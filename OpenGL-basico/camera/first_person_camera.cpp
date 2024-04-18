#include "first_person_camera.h"

void first_person_camera::move(const vector3& displacement)
{
    const auto forward = (direction_ - position_).normalize();

    const auto forward_movement = forward * displacement.get_z();
    const auto side_movement = up_ * forward * displacement.get_x();

    const auto movement = forward_movement + side_movement;

    position_ += movement;
    direction_ += movement;
}

void first_person_camera::rotate(const float x_offset, const float y_offset)
{
    constexpr float sensitivity = 0.01f; // Adjust this value to make the camera rotation more or less sensitive

    direction_.set_x(direction_.get_x() + x_offset * sensitivity);

    // Clamp the vertical rotation to be between -90 and 90 degrees
    if (direction_.get_y() - y_offset * sensitivity >= 90.0f)
        direction_.set_y(90.0f);
    else if (direction_.get_y() - y_offset * sensitivity <= -90.0f)
        direction_.set_y(-90.0f);
    else
        direction_.set_y(direction_.get_y() + y_offset * sensitivity);
}

void first_person_camera::zoom_in(const float amount)
{
    position_.set_z(position_.get_z() - amount);
}

void first_person_camera::zoom_out(const float amount)
{
    position_.set_z(position_.get_z() + amount);
}