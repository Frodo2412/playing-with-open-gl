#include "camera.h"

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

CameraMode camera::get_mode()
{
    return mode_;
}

bool camera::get_move_camera_first()
{
    return move_camera_first_;
}

float camera::get_perspective_zoom()
{
    return perspective_zoom_;
}

void camera::move(const vector3& displacement)
{
    const auto forward = (direction_ - position_).normalize();

    const auto forward_movement = forward * displacement.get_z();
    const auto side_movement = up_ * forward * displacement.get_x();

    const auto movement = forward_movement + side_movement;

    position_ += movement;
    direction_ += movement;
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

void camera::set_position(vector3 pos)
{
    position_ = pos;
}

void camera::set_direction(vector3 dir)
{
    direction_ = dir;
}

void camera::set_up(vector3 up)
{
    up_ = up;
}

void camera::set_mode(CameraMode mode)
{
    mode_ = mode;
}

void camera::set_move_camera_first(bool move_camera_first)
{
    move_camera_first_ = move_camera_first;
}

void camera::set_perspective_zoom(float perspective_zoom)
{
    perspective_zoom_ = perspective_zoom;
}


void camera::refresh(vector3 bomber_man)
{
    switch (this->get_mode())
    {
    case CameraMode::first:
        if (!this->get_move_camera_first())
        {
            this->set_direction(vector3(bomber_man.get_x(), bomber_man.get_y(), bomber_man.get_z()-5));
        }
        this->set_position(vector3(bomber_man.get_x(), bomber_man.get_y(), bomber_man.get_z()));
        break;
    case CameraMode::original:
        this->set_position(vector3 (0,10,0));
        this->set_direction(vector3 (0,0,0));
        this->set_up(vector3(0,0,-1));
        break;
    case CameraMode::perspective:
        this->set_position(vector3 (bomber_man.get_x(),bomber_man.get_y()+5+this->get_perspective_zoom(),bomber_man.get_z()+5));
        this->set_direction(vector3 (bomber_man.get_x(),0,bomber_man.get_z()));
        this->set_up(vector3(0,1,0));
        break;
    }
}

