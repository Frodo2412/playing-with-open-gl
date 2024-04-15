#include "Triangle.h"

#include <iostream>

vertex triangle::get_a() const
{
    return a_;
}

vertex triangle::get_b() const
{
    return b_;
}

vertex triangle::get_c() const
{
    return c_;
}

void triangle::an_op()
{
    std::cout << "Hola";
}

void triangle::set_a(const vertex& new_a)
{
    a_ = new_a;
}

void triangle::set_b(const vertex& new_b)
{
    b_ = new_b;
}

void triangle::set_c(const vertex& new_c)
{
    c_ = new_c;
}

void triangle::move(const vertex& other)
{
    a_ = a_ + other;
    b_ = b_ + other;
    c_ = c_ + other;
}

void triangle::move_left(const float distance)
{
    a_.set_x(a_.get_x() + distance);
    b_.set_x(b_.get_x() + distance);
    c_.set_x(c_.get_x() + distance);
}
