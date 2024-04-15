#pragma once
#include "vertex.h"

class triangle
{
    vertex a_, b_, c_;

public:
    // Constructor
    explicit triangle(const vertex& a = vertex(0, 0, 0), const vertex& b = vertex(0, 0, 0),
                      const vertex& c = vertex(0, 0, 0)) : a_(a), b_(b), c_(c)
    {
    }

    explicit triangle(const vertex& a)
    {
        const auto angle = a.angle_with(vertex(1, 0, 0));

        
    }

    // Getter methods for the vertexes
    vertex get_a() const;
    vertex get_b() const;
    vertex get_c() const;

    void an_op();

    // Setter methods for the coordinates
    void set_a(const vertex& new_a);
    void set_b(const vertex& new_b);
    void set_c(const vertex& new_c);

    void move(const vertex& other);
    void move_left(const float distance);
};
