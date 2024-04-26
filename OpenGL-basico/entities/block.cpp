#include "block.h"
#include "../textures/texture_loader.h"
#include "../geometry/cube.h"

texture block::metal_texture = texture_loader::load_texture("../assets/textures/metal_1.jpg");
texture block::brick_texture= texture_loader::load_texture("../assets/textures/bricks_1.jpg");

const texture block::get_texture()
{
    return texture_;
}

const vector3 block::get_posicion()
{
    return position_;
}

cube* block::get_block()
{
    return cube_;
}
