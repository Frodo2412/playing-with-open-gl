#include "camera.h"

#include <iostream>

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
    switch (mode_)
    {
    case first:
        {
            const auto forward = (direction_ - position_).normalize();

            const auto forward_movement = forward * displacement.get_z();
            const auto side_movement = up_ * forward * displacement.get_x();

            const auto movement = forward_movement + side_movement;

            position_ += movement;
            direction_ += movement;
        }
        break;
    case original:
        this->set_position(vector3(0, 10, 0));
        this->set_direction(vector3(0, 0, 0));
        this->set_up(vector3(0, 0, -1));
        break;
    case perspective:
        position_ += vector3(displacement.get_x(), displacement.get_y() + 5 + this->get_perspective_zoom(),
                             displacement.get_z() + 5);
        direction_ += vector3(displacement.get_x(), 0, displacement.get_z());
        direction_ += vector3(0, 1, 0);
        break;
    }
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

void camera::toggle_mode()
{
    switch (mode_)
    {
    case first:
        std::cout << "CAMERA CHANGED TO ORIGINAL\n";
        mode_ = original;
        break;
    case original:
        std::cout << "CAMERA CHANGED TO PERSPECTIVE\n";
        mode_ = perspective;
        break;
    case perspective:
        std::cout << "CAMERA CHANGED TO FIRST PERSON\n";
        mode_ = first;
        break;
    }
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
