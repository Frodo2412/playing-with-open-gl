#include "entity.h"

std::vector<vertex> entity::get_vertices() const
{
    return vertices_;
}

texture entity::get_texture() const
{
    return texture_;
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

float entity::get_scale_factor() const
{
    return scale_factor_;
}

aabb entity::get_bounding_box()
{
    const vector3 half_scale(scale_factor_ / 2);
    return {position_ - half_scale, position_ + half_scale};
}
