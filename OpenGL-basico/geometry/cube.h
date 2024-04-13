#pragma once
#include <array>

#include "square.h"
#include "vector.h"

class cube
{
    vector a_, b_, c_, d_, e_, f_, g_, h_;

public:
    explicit cube(const float size, const vector& center)
    {
        a_ = vector(center.get_x() - size / 2, center.get_y() - size / 2, center.get_z() - size / 2);
        b_ = vector(center.get_x() + size / 2, center.get_y() - size / 2, center.get_z() - size / 2);
        c_ = vector(center.get_x() + size / 2, center.get_y() + size / 2, center.get_z() - size / 2);
        d_ = vector(center.get_x() - size / 2, center.get_y() + size / 2, center.get_z() - size / 2);
        e_ = vector(center.get_x() - size / 2, center.get_y() - size / 2, center.get_z() + size / 2);
        f_ = vector(center.get_x() + size / 2, center.get_y() - size / 2, center.get_z() + size / 2);
        g_ = vector(center.get_x() + size / 2, center.get_y() + size / 2, center.get_z() + size / 2);
        h_ = vector(center.get_x() - size / 2, center.get_y() + size / 2, center.get_z() + size / 2);
    }

    std::array<square, 6> get_faces() const;
};
