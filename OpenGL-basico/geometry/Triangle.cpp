#include "Triangle.h"

vector triangle::get_a() const
{
    return a_;
}

vector triangle::get_b() const
{
    return b_;
}

vector triangle::get_c() const
{
    return c_;
}

void triangle::set_a(const vector& new_a)
{
    a_ = new_a;
}

void triangle::set_b(const vector& new_b)
{
    b_ = new_b;
}

void triangle::set_c(const vector& new_c)
{
    c_ = new_c;
}
