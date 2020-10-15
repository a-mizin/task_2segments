#include "geometry.h"

Vector3D::Vector3D(const double x, const double y, const double z) :
    x_(x), y_(y), z_(z) {}

Vector3D Vector3D::operator-(const Vector3D& lhs) const {
    return Vector3D(x_ - lhs.x_, y_ - lhs.y_, z_ - lhs.z_);
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
