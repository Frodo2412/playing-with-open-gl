#pragma once
#include "scene.h"

class level final : public scene
{
    explicit level(const int grid_width, const int grid_height): scene()
    {
        floor_ = grid(grid_width, grid_height, 1, vector3(0, 1, 0));
    }

public:
    static level level1();
};
