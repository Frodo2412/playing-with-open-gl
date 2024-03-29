#pragma once
#include "vector.h"

class triangle
{
    vector a_, b_, c_;

public:
    // Constructor
    explicit triangle(const vector& a = vector(0, 0, 0), const vector& b = vector(0, 0, 0),
                      const vector& c = vector(0, 0, 0)) : a_(a), b_(b), c_(c)
    {
    }

    // Getter methods for the vertexes
    vector get_a() const;
    vector get_b() const;
    vector get_c() const;

    // Setter methods for the coordinates
    void set_a(const vector& new_a);
    void set_b(const vector& new_b);
    void set_c(const vector& new_c);
};
