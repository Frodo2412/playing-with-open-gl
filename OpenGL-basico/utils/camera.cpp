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
