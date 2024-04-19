#include "scene.h"

#include <GL/glu.h>

#include "../utils/renderer.h"

void scene::toggle_camera()
{
    switch (camera_mode_)
    {
    case first:
        camera_mode_ = top_down;
        camera_->set_position(vector3(0, 10, 0));
        camera_->set_direction(vector3(0, 0, 0));
        camera_->set_up(vector3(0, 0, -1));
        break;
    case top_down:
        {
            camera_mode_ = perspective;
            const auto player = player_->get_direction();
            camera_->set_position(vector3(player.get_x(), player.get_y(), player.get_z() + 5));
            break;
        }
    case perspective:
        camera_mode_ = first;
        camera_->set_direction(player_->get_direction());
        camera_->set_position(player_->get_position());
        break;
    }
}

void scene::rotate_camera(const float x, const float y) const
{
    switch (camera_mode_)
    {
    case first:
        camera_->rotate(x, y);
        player_->set_direction(camera_->get_direction());
        break;
    default: break;
    }
}

void scene::move_player(const vector3& displacement) const
{
    switch (camera_mode_)
    {
    case first:
        {
            const auto direction = camera_->get_direction();
            const auto position = camera_->get_position();
            const auto up = camera_->get_up();

            const auto forward = (direction - position).normalize();

            const auto forward_movement = forward * displacement.get_z();
            const auto side_movement = up * forward * displacement.get_x();

            const auto movement = forward_movement + side_movement;

            camera_->move(movement);
            player_->move(movement);
            break;
        }
    case top_down:
        player_->move(-displacement);
        player_->set_direction(-displacement);
        break;
    case perspective:
        camera_->move(-displacement);
        player_->move(-displacement);
        player_->set_direction(-displacement);
        break;
    }
}

void scene::render_scene() const
{
    gluLookAt(camera_->get_position().get_x(), camera_->get_position().get_y(), camera_->get_position().get_z(),
              camera_->get_direction().get_x(), camera_->get_direction().get_y(),
              camera_->get_direction().get_z(),
              camera_->get_up().get_x(), camera_->get_up().get_y(), camera_->get_up().get_z());
    renderer::draw(*player_);
}