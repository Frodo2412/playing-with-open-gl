#include "game_object.h"

bool game_object::check_collision(const aabb& other)
{
    const auto a = get_bounding_box();
    return a.min.get_x() <= other.max.get_x() && a.max.get_x() >= other.min.get_x() &&
        (a.min.get_y() <= other.max.get_y() && a.max.get_y() >= other.min.get_y()) &&
        (a.min.get_z() <= other.max.get_z() && a.max.get_z() >= other.min.get_z());
}

vector3 game_object::get_position() const
{
    return position_;
}

texture game_object::get_texture() const
{
    return texture_;
}
