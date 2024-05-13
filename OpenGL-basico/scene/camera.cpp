#include "camera.h"
#include <iostream>
#include "../entities/player.h"

vector3 camera::get_position() const
{
    return position_;
}

vector3 camera::get_direction() const
{
    return direction_;
}

vector3 camera::get_up() const
{
    return up_;
}

void camera::set_direction(const vector3& direction)
{
    direction_ = direction;
}

void camera::set_position(const vector3& position)
{
    position_ = position;
}

void camera::set_up(const vector3& up)
{
    up_ = up;
}

void camera::move(const vector3& displacement)
{
    direction_ += displacement;
    position_ += displacement;
}

void camera::move(const player* player)
{
    // Predict new position based on player speed
    auto new_position = position_ + player->get_speed();

    // Get player's bounding box
    const aabb entity_box = player->get_bounding_box();

    // Constrain new position within the bounding box
    new_position.set_x(std::max(entity_box.min.get_x(),
                                std::min(entity_box.max.get_x(), new_position.get_x())));
    new_position.set_y(std::max(entity_box.min.get_y(),
                                std::min(entity_box.max.get_y(), new_position.get_y())));
    new_position.set_z(std::max(entity_box.min.get_z(),
                                std::min(entity_box.max.get_z(), new_position.get_z())));

    // Set camera's new constrained position
    position_ = new_position;
    direction_ += player->get_speed();
}

void camera::rotate(const float x_offset, const float y_offset, bool first)
{
    constexpr float sensitivity = 0.005f; 
    if(first)
    {
        if(position_.get_z() <= 0.0f)
        {
            direction_.set_x(direction_.get_x() - x_offset * sensitivity);
        }else
        {
            direction_.set_x(direction_.get_x() + x_offset * sensitivity);
        }
    }else
    {
        direction_.set_x(direction_.get_x() - x_offset * sensitivity);
    }
    if (direction_.get_y() - y_offset * sensitivity >= 90.0f)
        direction_.set_y(90.0f);
    else if (direction_.get_y() - y_offset * sensitivity <= -90.0f)
        direction_.set_y(-90.0f);
    else
        direction_.set_y(direction_.get_y() + y_offset * sensitivity);
}