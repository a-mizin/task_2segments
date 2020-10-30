#include "Segment3D.h"

Segment3D::Segment3D(const Vector3D& start, const Vector3D& end) :
        start_(start), end_(end) {}

bool Segment3D::operator==(const Segment3D &rhs) const {
    return start_ == rhs.start_ && end_ == rhs.end_;
}

Vector3D Segment3D::pointFromLine(double u) const {
    return start_.scalarMultiplication(u) +
           end_.scalarMultiplication(1. - u);
}

bool Segment3D::isPoint() const {
    return start_ == end_;
}
