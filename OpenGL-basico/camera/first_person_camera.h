#pragma once
#include "camera.h"
#include "../entities/player.h"


class first_person_camera final : public camera
{
public:
    first_person_camera(const float x, const float y, const float z): camera(x, y, z)
    {
    }

    void move(const vector3& displacement) override;
    void rotate(float x_offset, float y_offset) override;

    void zoom_in(float amount) override;
    void zoom_out(float amount) override;
};
