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
camera::~camera() = default;

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
