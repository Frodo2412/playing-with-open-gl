#include "entity.h"

std::vector<vertex> entity::get_vertices() const
{
    return vertices_;
}

texture entity::get_texture() const
{
    return texture_;
}

vector3 entity::get_position() const
{
    return position_;
}

void entity::move(const vector3& displacement)
{
    position_ += displacement;
}
