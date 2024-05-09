#pragma once
#include "coordinate.h"
#include "scene.h"

class level final : public scene
{
public:
    explicit level(int grid_width, int grid_height, vector3 initial_player_position,
                   std::vector<coordinate> metal_blocks, std::vector<coordinate> brick_blocks,
                   std::vector<coordinate> enemies_positions, std::vector<coordinate> enemies);

    static level level1();
    
};
