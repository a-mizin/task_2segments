#pragma once

struct Vector3D {
    Vector3D(const double x, const double y, const double z);

    Vector3D scalarMultiplication(const double scalar) const;

    Vector3D operator-(const Vector3D& lhs) const;
    Vector3D operator+(const Vector3D& lhs) const;

    bool operator!=(const Vector3D& lhs) const;
    bool operator==(const Vector3D& lhs) const;

    bool operator<(const Vector3D& lhs) const;

public:
    double x_;
    double y_;
    double z_;
};
