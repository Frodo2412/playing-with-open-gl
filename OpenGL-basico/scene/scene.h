#pragma once
#include "../scene/camera.h"
#include "../entities/player.h"

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
    camera* camera_;

public:
    explicit scene(player* player)
        : player_(player),
          camera_(new camera(0, 0, 5))
    {
    }

    // Camera related functionality
    void toggle_camera();
    void rotate_camera(const float x, const float y) const;

    void move_player(const vector3& displacement) const;

    void render_scene() const;
};
