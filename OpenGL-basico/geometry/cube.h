#pragma once
#include <array>

#include "square.h"
#include "vertex.h"

class cube
{
    vertex a_, b_, c_, d_, e_, f_, g_, h_;

public:
    explicit cube(const float size, const vertex& center)
    {
        a_ = vertex(center.get_x() - size / 2, center.get_y() - size / 2, center.get_z() - size / 2);
        b_ = vertex(center.get_x() + size / 2, center.get_y() - size / 2, center.get_z() - size / 2);
        c_ = vertex(center.get_x() + size / 2, center.get_y() + size / 2, center.get_z() - size / 2);
        d_ = vertex(center.get_x() - size / 2, center.get_y() + size / 2, center.get_z() - size / 2);
        e_ = vertex(center.get_x() - size / 2, center.get_y() - size / 2, center.get_z() + size / 2);
        f_ = vertex(center.get_x() + size / 2, center.get_y() - size / 2, center.get_z() + size / 2);
        g_ = vertex(center.get_x() + size / 2, center.get_y() + size / 2, center.get_z() + size / 2);
        h_ = vertex(center.get_x() - size / 2, center.get_y() + size / 2, center.get_z() + size / 2);
    }

    std::array<square, 6> get_faces() const;
};
