#include "level.h"

level::level(int grid_width, int grid_height, vector3 initial_player_position, std::vector<coordinate> metal_blocks,
             std::vector<coordinate> brick_blocks, std::vector<coordinate> enemies_positions,
             std::vector<coordinate> enemies)
{
    enemies_.emplace_back(std::make_unique<enemy>(enemy()));
    blocks_.push_back(std::make_unique<brick_block>(vector3(0.5, -0.5, 0)));
    blocks_.push_back(std::make_unique<brick_block>(vector3(1.5, -0.5, 0)));
    blocks_.push_back(std::make_unique<metal_block>(vector3(2.5, -0.5, 0)));
    blocks_.push_back(std::make_unique<metal_block>(vector3(1.5, -0.5, 1)));
}

level level::level1()
{
    return level(17, 11, vector3::zero(), std::vector<coordinate>(), std::vector<coordinate>(),
                 std::vector<coordinate>(), std::vector<coordinate>());
}
