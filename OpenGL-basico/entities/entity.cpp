#include "entity.h"

std::vector<vertex> entity::get_vertices() const
{
    return vertices_;
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

void entity::set_speed(const vector3& speed)
{
    speed_ = speed;
}

void entity::move()
{
    position_ += speed_;
}

float entity::get_scale_factor() const
{
    return scale_factor_;
}

bool entity::check_collision(const game_object* other_object) const
{
    const auto a = get_bounding_box();
    const aabb other = other_object->get_bounding_box();
    return a.min.get_x() <= other.max.get_x() && a.max.get_x() >= other.min.get_x() &&
        (a.min.get_y() <= other.max.get_y() && a.max.get_y() >= other.min.get_y()) &&
        (a.min.get_z() <= other.max.get_z() && a.max.get_z() >= other.min.get_z());
}

aabb entity::get_bounding_box() const
{
    return {bounding_box_.min + position_, bounding_box_.max + position_};
}

float entity::get_scale_factor() const
{
    return scale_factor_;
}
