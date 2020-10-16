#include "Segment3D.h"

Segment3D::Segment3D(const Vector3D& start, const Vector3D& end) :
        start_(start), end_(end) {}

Vector3D
Segment3D::pointFromLine(double u) const {
    return start_.scalarMultiplication(u) +
           end_.scalarMultiplication(1. - u);
}
