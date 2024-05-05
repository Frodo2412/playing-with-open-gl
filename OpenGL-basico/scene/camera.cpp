#include "camera.h"

#include <iostream>

// void camera::move(const vector3& displacement)
// {
//     switch (mode_)
//     {
//     case first:
//         {
//             const auto forward = (direction_ - position_).normalize();
//
//             const auto forward_movement = forward * displacement.get_z();
//             const auto side_movement = up_ * forward * displacement.get_x();
//
//             const auto movement = forward_movement + side_movement;
//
//             position_ += movement;
//             direction_ += movement;
//         }
//         break;
//     case original:
//         this->set_position(vector3(0, 10, 0));
//         this->set_direction(vector3(0, 0, 0));
//         this->set_up(vector3(0, 0, -1));
//         break;
//     case perspective:
//         position_ += vector3(displacement.get_x(), displacement.get_y() + this->get_perspective_zoom(),
//                              displacement.get_z());
//         direction_ += vector3(displacement.get_x(), 0, displacement.get_z());
//         direction_ += vector3(0, 1, 0);
//         break;
//     }
// }

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

void camera::rotate(const float x_offset, const float y_offset)
{
    constexpr float sensitivity = 0.005f; // Adjust this value to make the camera rotation more or less sensitive

    direction_.set_x(direction_.get_x() - x_offset * sensitivity);

    // Clamp the vertical rotation to be between -90 and 90 degrees
    if (direction_.get_y() - y_offset * sensitivity >= 90.0f)
        direction_.set_y(90.0f);
    else if (direction_.get_y() - y_offset * sensitivity <= -90.0f)
        direction_.set_y(-90.0f);
    else
        direction_.set_y(direction_.get_y() + y_offset * sensitivity);

}
