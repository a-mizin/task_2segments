#pragma once

#include "../vectorLib/Vector3D.h"

class Segment3D {
    friend Vector3D
    intersect(const Segment3D& s1, const Segment3D& s2);

public:
    Segment3D(const Vector3D& start, const Vector3D& end);

    Vector3D
    pointFromLine(double u) const;

private:
    Vector3D start_;
    Vector3D end_;
};