#pragma once
#include "../entities/enemy.h"
#include "../scene/camera.h"
#include "../entities/player.h"
#include "../entities/block.h"

enum camera_mode
{
    first,
    top_down,
    perspective
};


class scene
{
    camera_mode camera_mode_ = first;

    player* player_;
    std::vector<enemy> enemies_;

    camera* camera_;

public:
    explicit scene(player* player, const vector3& initial_player_position)
        : player_(player),
          camera_(new camera(initial_player_position.get_x(), initial_player_position.get_y(),
                             initial_player_position.get_z()))
    {
        player_->set_position(initial_player_position);
        enemies_.emplace_back();
    }

    // Camera related functionality
    void toggle_camera();
    void rotate_camera(const float x, const float y) const;

    void move_player(const vector3& displacement) const;
    camera_mode get_camera_mode();
    camera* get_camera();
    void drop_bomb(std::vector<block*>& bloques);
    void render_scene() const;
};
