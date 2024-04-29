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
            const auto player_position = player_->get_position();
            camera_->set_position(player_position + vector3(0, 10, 5));
            camera_->set_direction(player_position);
            camera_->set_up(vector3(0, 0, -1));
            break;
        }
    case perspective:
        camera_mode_ = first;
        camera_->set_up(player_->get_up());
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
    case perspective:
        glRotatef(x, player_->get_position().get_x(), 1, player_->get_position().get_z());
        break;
    case top_down:
        break;
    }
}

void scene::update_scene() const
{
    player_->move();

    for (auto& block : blocks_)
        if (player_->check_collision(block.get()))
            player_->handle_collision(block.get());

    for (auto& enemy : enemies_)
    {
        if (player_->check_collision(enemy.get()))
            player_->handle_collision(enemy.get());
        enemy.get()->move();
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

            auto movement = forward_movement + side_movement;

            movement.set_y(0);

            camera_->move(movement);
            player_->set_speed(movement);
            break;
        }
    case top_down:
        {
            const auto movement = -displacement;
            player_->set_speed(movement);
            player_->set_direction(movement);
            break;
        }
    case perspective:
        {
            const auto movement = -displacement;
            player_->set_speed(movement);
            player_->set_direction(movement);
            camera_->move(movement);
            break;
        }
    }
}

void scene::render_scene() const
{
    gluLookAt(camera_->get_position().get_x(), camera_->get_position().get_y(), camera_->get_position().get_z(),
              camera_->get_direction().get_x(), camera_->get_direction().get_y(),
              camera_->get_direction().get_z(),
              camera_->get_up().get_x(), camera_->get_up().get_y(), camera_->get_up().get_z());
    renderer::draw(*player_);

    for (auto& enemy : enemies_)
    {
        renderer::draw(*enemy.get());
    }
    for (const auto& block : blocks_)
    {
        renderer::draw(block->get_block(), block->get_texture());
    }
}

camera_mode scene::get_camera_mode() const
{
    return camera_mode_;
}

camera* scene::get_camera() const
{
    return camera_;
}
