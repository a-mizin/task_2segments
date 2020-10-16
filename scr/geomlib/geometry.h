#include <tuple>

class Vector3D {
    friend  double compDeterminant3D(const Vector3D& vector1,
                                     const Vector3D& vector2,
                                     const Vector3D& vector3);
    friend  std::tuple<double, double>
            solveLinearSystem2D(Vector3D vec1, Vector3D vec2,
                                Vector3D vector3);
public:
    Vector3D(double x, double y, double z);

    Vector3D scalarMultiplication(double scalar) const;

    Vector3D operator-(const Vector3D& lhs) const;
    Vector3D operator+(const Vector3D& lhs) const;
    bool operator==(const Vector3D& lhs) const;
    bool operator<(const Vector3D& lhs) const;
    bool operator!=(const Vector3D& lhs) const;

private:
    double x_;
    double y_;
    double z_;
};

Vector3D operator*(double scalar, Vector3D vector);

class Segment3D {
    friend Vector3D intersect(const Segment3D& segment1,
                              const Segment3D& segment2);
public:
    Segment3D(Vector3D start, Vector3D end);

private:
    Vector3D start_;
    Vector3D end_;
};

double compDeterminant3D(const Vector3D& vector1, const Vector3D& vector2,
                         const Vector3D& vector3);

std::tuple<double, double>
        solveLinearSystem2D(Vector3D vec1, Vector3D vec2,
                            Vector3D vector3);

Vector3D intersect(const Segment3D& segment1, const Segment3D& segment2);