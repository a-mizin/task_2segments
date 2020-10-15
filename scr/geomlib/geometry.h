
class Vector3D {
public:
    Vector3D(double x, double y, double z);
    Vector3D operator-(const Vector3D& lhs) const;
private:
    friend  double compDeterminant3D(const Vector3D& vector1,
                                     const Vector3D& vector2,
                                     const Vector3D& vector3);

    double x_;
    double y_;
    double z_;
};

class Segment3D {
public:
    Segment3D(Vector3D start, Vector3D end);

private:
    Vector3D start_;
    Vector3D end_;
};

double compDeterminant3D(const Vector3D& vector1, const Vector3D& vector2,
                         const Vector3D& vector3);