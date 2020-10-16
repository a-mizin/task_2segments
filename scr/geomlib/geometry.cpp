#include <exception>
#include <algorithm>

#include "geometry.h"

Vector3D::Vector3D(const double x, const double y, const double z) :
    x_(x), y_(y), z_(z) {}

Vector3D Vector3D::scalarMultiplication(double scalar) const {
    return Vector3D(scalar * x_, scalar * y_, scalar * z_);
}

Vector3D Vector3D::operator-(const Vector3D& lhs) const {
    return Vector3D(x_ - lhs.x_, y_ - lhs.y_, z_ - lhs.z_);
}

Vector3D Vector3D::operator+(const Vector3D &lhs) const {
    return Vector3D(x_ + lhs.x_, y_ + lhs.y_, z_ + lhs.z_);
}

bool Vector3D::operator==(const Vector3D &lhs) const {
    return std::tie(x_, y_, z_) == std::tie(lhs.x_, lhs.y_, lhs.z_);
}

bool Vector3D::operator<(const Vector3D &lhs) const {
    return std::tie(x_, y_, z_) < std::tie(lhs.x_, lhs.y_, lhs.z_);
}

bool Vector3D::operator!=(const Vector3D &lhs) const {
    return std::tie(x_, y_, z_) != std::tie(lhs.x_, lhs.y_, lhs.z_);
}

Segment3D::Segment3D(const Vector3D start, const Vector3D end) :
    start_(start), end_(end) {}

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
        solveLinearSystem2D(Vector3D vec1, Vector3D vec2, Vector3D a)
{
    double u, v;
    if (double det = vec1.x_ * vec2.y_ - vec1.y_ * vec2.x_; det == 0) {
        throw std::exception("Infinite number of solutions.");
    } else {
        u = (a.x_ * vec2.y_ - vec2.x_ * a.y_) / det;
        v = (vec1.x_ * a.y_ - a.x_ * vec1.y_) / det;
    }

    return std::tie(u, v);
}

Vector3D intersect(const Segment3D &AB, const Segment3D &CD) {
    Vector3D BA(AB.start_ - AB.end_);
    Vector3D DC(CD.end_   - CD.start_); //rename
    Vector3D BD(CD.end_   - AB.end_);
    Vector3D AC(CD.start_ - AB.start_);

    //Not coplanar segments do not intersect
    if (compDeterminant3D(BA, DC, AC) != 0)
        throw std::exception("Coplanar segments.");

    //solve system u*BA - v*DC = BD; u, v - scalar
    double u, v;
    try {
        std::tie(u, v) = solveLinearSystem2D(BA, DC, BD);
    }
    catch (std::exception& exception) {
        //throw std::exception("????");
        if (std::max(AB.start_, AB.end_) != std::min(CD.start_, CD.end_))
            throw std::exception("Do not intersect.");
        else
            return std::max(AB.start_, AB.end_);
    }

    if (u < 0. || u > 1. || v < 0. || v > 1.)
        throw std::exception("Do not intersect.");

    return  AB.start_.scalarMultiplication(u) +
            AB.end_.scalarMultiplication(1 - u);
}
