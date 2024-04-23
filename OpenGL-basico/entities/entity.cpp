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

vector3 entity::get_direction() const
{
    return direction_;
}

vector3 entity::get_up() const
{
    return up_;
}

void entity::set_direction(const vector3& direction)
{
    direction_ = direction;
}

void entity::set_position(const vector3& position)
{
    position_ = position;
}

void entity::move(const vector3& displacement)
{
    position_ += displacement;
}
