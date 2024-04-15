#pragma once
#include "vertex.h"

class square
{
    vertex a_, b_, c_, d_;

public:
    explicit square(const vertex& a, const vertex& b, const vertex& c, const vertex& d)
        : a_(a), b_(b), c_(c), d_(d)
    {
    }

    const vertex& get_a() const;
    const vertex& get_b() const;
    const vertex& get_c() const;
    const vertex& get_d() const;
};
