#include <exception>
#include <algorithm>

#include "../segmentLib/Segment3D.h"

double compDeterminant3D(const Vector3D& v1, const Vector3D& v2,
                         const Vector3D& v3)
{
    return  v1.x_ * v2.y_ * v3.z_ +
            v2.x_ * v3.y_ * v1.z_ +
            v3.x_ * v1.y_ * v2.z_ -
            v3.x_ * v2.y_ * v1.z_ -
            v2.x_ * v1.y_ * v3.z_ -
            v1.x_ * v3.y_ * v2.z_;
}

std::tuple<double, double>
solveLinearSystem2D(const Vector3D& v1, const Vector3D& v2,
                    const Vector3D& a)
{
    double u, v;
    if (double det = v1.x_ * v2.y_ - v1.y_ * v2.x_; det == 0) {
        throw std::exception("Infinite number of solutions.");
    } else {
        u = (a.x_ * v2.y_ - v2.x_ * a.y_) / det;
        v = (v1.x_ * a.y_ - a.x_ * v1.y_) / det;
    }

    return std::tie(u, v);
}

double convexCombinationCoefficient(const Vector3D &v1, const Vector3D &v2,
                                    const Vector3D &v3)
{
    // let v1 is vector OA, v2 is vector OB, v3 is vector OC
    Vector3D BA(v1 - v2);
    Vector3D BC(v3 - v2);

    double u;
    bool isInitialized = false;

    if (BA.x_ != 0.) {
        u = BC.x_ / BA.x_;
        isInitialized = true;
    }

    if (BA.y_ != 0.) {
        if (isInitialized && u != BC.y_ / BA.y_)
                throw std::exception("The point is not on the segment.");

        u = BC.y_ / BA.y_;
        isInitialized = true;
    }

    if (BA.z_ != 0.) {
        if (isInitialized && u != BC.z_ / BA.z_)
            throw std::exception("The point is not on the segment.");
        u = BC.z_ / BA.z_;
        isInitialized = true;
    }

    if (isInitialized)
        return u;
    else
        throw std::exception("There is a point, not a segment.");
}

Vector3D intersect(const Segment3D &s1, const Segment3D &s2) {
    // let s1 is segment AB, s2 is segment CD
    Vector3D BA(s1.start_ - s1.end_);
    Vector3D CD(s2.end_   - s2.start_);
    Vector3D BD(s2.end_   - s1.end_);
    Vector3D AC(s2.start_ - s1.start_);

    //Not coplanar vectors
    if (compDeterminant3D(BA, CD, AC) != 0.) // две точки пересекаются и не пересекаются???
        throw std::exception("Do not intersect.");

    //solve system u*BA - v*CD = BD; u, v - scalar
    double u, v;
    try {
        std::tie(u, v) = solveLinearSystem2D(BA, CD, BD);

        if (u < 0. || u > 1. || v < 0. || v > 1.)
            throw std::exception("Do not intersect.");

        return s1.pointFromLine(u);
    }
    catch (std::exception& exception) {
        //Two segments - points
        if (s1.start_ == s1.end_ && s2.start_ == s2.end_) {
            if (s1.start_ == s2.start_)
                return s1.start_;

            throw std::exception("Do not intersect.");
        }

        const Segment3D& segment  = (s1.start_ == s1.end_) ? s2 : s1;
        const Segment3D& pointOrSegment = (s1.start_ == s1.end_) ? s1 : s2;

        //solve u * segment.start_ + (1 - u)segment.end_
        //          = pointOrSegment.start_
        //          u - scalar
        u = convexCombinationCoefficient(
                segment.start_, segment.end_, pointOrSegment.start_);
        if (u < 0. && u > 1.)
            //solve u * segment.start_ + (1 - u)segment.end_
            //          = pointOrSegment.end_
            //          u - scalar
            u = convexCombinationCoefficient(
                    segment.start_, segment.end_, pointOrSegment.end_);

        if (0. <= u && u <= 1.)
            return segment.pointFromLine(u);

        throw std::exception("Do not intersect.");
    }
}