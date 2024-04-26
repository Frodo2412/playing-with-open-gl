#pragma once
#include "block.h"
#include "../geometry/vector3.h"
#include "../textures/texture_loader.h"

class metal_block : public block
{
    texture texture_;
    bool destructible_ = false;
public:
    metal_block(const vector3& pos): block(pos), texture_(texture_loader::load_texture("../assets/textures/metal_1.jpg")) {};
     const texture get_texture() override;
};