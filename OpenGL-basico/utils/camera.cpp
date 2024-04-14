#include "camera.h"

vector camera::get_position() const
{
    return position_;
}

vector camera::get_direction() const
{
    return direction_;
}

vector camera::get_up() const
{
    return up_;
}

void camera::move(const vector& displacement)
{
    position_ += displacement;
    direction_ += displacement;
}

void camera::zoom_in(const float amount)
{
    position_.set_z(position_.get_z() - amount);
}

void camera::zoom_out(const float amount)
{
    position_.set_z(position_.get_z() + amount);
}

void camera::rotate(const float x_offset, const float y_offset)
{
    constexpr float sensitivity = 0.001f; // Adjust this value to make the camera rotation more or less sensitive

    direction_.set_x(direction_.get_x() + x_offset * sensitivity);

    // Clamp the vertical rotation to be between -90 and 90 degrees
    if (direction_.get_y() - y_offset * sensitivity >= 90.0f)
        direction_.set_y(90.0f);
    else if (direction_.get_y() - y_offset * sensitivity <= -90.0f)
        direction_.set_y(-90.0f);
    else
        direction_.set_y(direction_.get_y() + y_offset * sensitivity);
}
