#pragma once
#include "camera.h"

class top_down_camera final : public camera
{
public:
    explicit top_down_camera(): camera(vector3(0, 10, 0), vector3(0, 0, 0), vector3(0, 0, -1))
    {
    }

    void move(const vector3& displacement) override;
    void rotate(float x_offset, float y_offset) override;

    void zoom_in(float amount) override;
    void zoom_out(float amount) override;
};
