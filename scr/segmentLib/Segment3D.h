#pragma once

#include "../vectorLib/Vector3D.h"

struct Segment3D {
    Segment3D(const Vector3D& start, const Vector3D& end);

    bool operator==(const Segment3D& rhs) const;

    Vector3D pointFromLine(const double u) const;

    bool isPoint() const;

public:
    Vector3D start_;
    Vector3D end_;
};