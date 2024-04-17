#pragma once
#include "camera.h"

class top_down_camera final : public camera
{
public:
    void move(const vector3& displacement) override;
    void rotate(float x_offset, float y_offset) override;

    void zoom_in(float amount) override;
    void zoom_out(float amount) override;
};
