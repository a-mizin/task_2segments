#include <stdexcept>
#include <limits>
#include <cmath>
#include <vector>
#include <tuple>

#include "../segmentLib/Segment3D.h"

namespace {
    bool inUnitLine(const double point) {
        return 0. <= point && point <= 1.;
    }

    bool isEqual(const double lhs, const double rhs,
                 const double eps)
    {
        return std::fabs(lhs - rhs) < eps;
    }

    bool isEqual(const Vector3D& lhs, const Vector3D& rhs,
                 const double eps)
    {
        return  isEqual(lhs.x_, rhs.x_, eps) &&
                isEqual(lhs.y_, rhs.y_, eps) &&
                isEqual(lhs.z_, lhs.z_, eps);
    }

    bool isEqual(const Segment3D& lhs, const Segment3D& rhs,
                 const double eps)
    {
        return  isEqual(lhs.start_, rhs.start_, eps) &&
                isEqual(lhs.end_  , rhs.end_  , eps);
    }

    bool isPoint(const Segment3D& segment,
                 const double eps)
    {
        return isEqual(segment.start_, segment.end_, eps);
    }

    double compDeterminant3D(const Vector3D& v1, const Vector3D& v2,
                             const Vector3D& v3) {
        return v1.x_ * v2.y_ * v3.z_ +
               v2.x_ * v3.y_ * v1.z_ +
               v3.x_ * v1.y_ * v2.z_ -
               v3.x_ * v2.y_ * v1.z_ -
               v2.x_ * v1.y_ * v3.z_ -
               v1.x_ * v3.y_ * v2.z_;
    }

    std::pair<bool, double>
    convexCombination(const Segment3D& s, const Vector3D& v,
                      const double eps)
    {
        std::vector<double> coeff;

        if (double factor = s.start_.x_ - s.end_.x_;
            !isEqual(factor, 0, eps))
        {
            coeff.push_back( (v.x_ - s.end_.x_) / factor );
        }

        if (double factor = s.start_.y_ - s.end_.y_;
            !isEqual(factor, 0, eps))
        {
            coeff.push_back( (v.y_ - s.end_.y_) / factor );
        }

        if (double factor = s.start_.z_ - s.end_.z_;
            !isEqual(factor, 0, eps))
        {
            coeff.push_back( (v.z_ - s.end_.z_) / factor );
        }

        switch (coeff.size()) {
            case 0:
                throw std::invalid_argument("");
            case 1:
                return std::make_pair(true, coeff[0]);
            case 2:
                if (coeff[0] == coeff[1])
                    return std::make_pair(true, coeff[0]);
                else
                    return std::make_pair(false, -1);
            case 3:
                if (coeff[0] == coeff[1] && coeff[0] == coeff[2])
                    return std::make_pair(true, coeff[0]);
                else
                    return std::make_pair(false, -1);
        }
    }
}

Vector3D intersect(const Segment3D& segmentAB, const Segment3D& segmentCD,
                   const double eps = std::numeric_limits<double>::epsilon()) {
    // let s1 is segment AB, segmentCD is segment CD
    Vector3D BA(segmentAB.start_ - segmentAB.end_   );
    Vector3D CD(segmentCD.end_   - segmentCD.start_ );
    Vector3D BD(segmentCD.end_   - segmentAB.end_   );
    Vector3D AC(segmentCD.start_ - segmentAB.start_ );

    //Not coplanar vectors
    if (!isEqual(compDeterminant3D(BA, CD, AC), 0, eps))
        throw std::invalid_argument("Do not intersect.");

    //solve system u*BA - v*CD = BD; u, v - scalar
    double det = BA.x_ * CD.y_ - BA.y_ * CD.x_;
    if (!isEqual(det, 0, eps)) {
        double u, v;
        u = (BD.x_ * CD.y_  - CD.x_ * BD.y_) / det;
        v = (BA.x_ * BD.y_  - BD.x_ * BA.y_) / det;

        if (inUnitLine(u) && inUnitLine(v))
            return segmentAB.pointFromLine(u);

        throw std::invalid_argument("Do not intersect.");
    }

    // 1)       Two segments - points
    if (isPoint(segmentAB, eps) && isPoint(segmentCD, eps)) {
        if (isEqual(segmentAB, segmentCD, eps))
            //point A from segment AB
            return segmentAB.pointFromLine(0);

        throw std::invalid_argument("Do not intersect.");
    }

    // 2)       One of the sections is definitely not a point
    const Segment3D& segment        = segmentAB.isPoint() ? segmentCD : segmentAB;
    const Segment3D& pointOrSegment = segmentAB.isPoint() ? segmentAB : segmentCD;

    double u;
    bool isCombination;
    std::tie(isCombination, u) = convexCombination(segment, pointOrSegment.start_, eps);
    if (!isCombination || !inUnitLine(u))
         std::tie(isCombination, u)= convexCombination(segment, pointOrSegment.end_, eps);
    if (!isCombination || !inUnitLine(u))
        throw std::invalid_argument("Do not intersect.");

    return segment.pointFromLine(u);
}