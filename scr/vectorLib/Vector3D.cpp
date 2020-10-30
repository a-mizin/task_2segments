#include <tuple>
#include "Vector3D.h"

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
