#pragma once
#include "vector.h"

class square
{
    vector a_, b_, c_, d_;

public:
    explicit square(const vector& a, const vector& b, const vector& c, const vector& d)
        : a_(a), b_(b), c_(c), d_(d)
    {
    }

    const vector& get_a() const;
    const vector& get_b() const;
    const vector& get_c() const;
    const vector& get_d() const;
};
