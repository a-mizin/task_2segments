#pragma once

#include <tuple>

class Vector3D {
    friend  double
    compDeterminant3D(const Vector3D& vector1,const Vector3D& vector2,
                      const Vector3D& vector3);

    friend  std::tuple<double, double>
    solveLinearSystem2D(const Vector3D& vector1, const Vector3D& vector2,
                        const Vector3D& vector3);

    friend double
    convexCombinationCoefficient(const Vector3D& vector1, const Vector3D& vector2,
                                 const Vector3D& vector3);

public:
    Vector3D(double x, double y, double z);

    Vector3D
    scalarMultiplication(double scalar) const;

    Vector3D
    operator-(const Vector3D& lhs) const;

    Vector3D
    operator+(const Vector3D& lhs) const;

    bool
    operator==(const Vector3D& lhs) const;

    bool
    operator<(const Vector3D& lhs) const;

    bool
    operator!=(const Vector3D& lhs) const;

private:
    double x_;
    double y_;
    double z_;
};
