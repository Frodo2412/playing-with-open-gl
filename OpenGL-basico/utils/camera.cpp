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
    direction_.set_x(direction_.get_x() + x_offset / 10);
    direction_.set_y(direction_.get_y() + y_offset / 10);
}
