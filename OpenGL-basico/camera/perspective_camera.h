#pragma once
#include "camera.h"

class perspective_camera final : public camera
{
public:
    explicit perspective_camera(const vector3 player): camera(
        player, vector3(player.get_x(), player.get_y(), player.get_z() + 5), vector3(0, 1, 0))
    {
    }

    void move(const vector3& displacement) override;
    void rotate(float x_offset, float y_offset) override;

    void zoom_in(float amount) override;
    void zoom_out(float amount) override;
};
