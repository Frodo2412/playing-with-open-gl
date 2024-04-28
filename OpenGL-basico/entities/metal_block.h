#pragma once
#include "block.h"
#include "../geometry/vector3.h"
#include "../textures/texture_manager.h"

class metal_block : public block
{
    bool destructible_ = false;

public:
    explicit metal_block(const vector3& position): block(position, texture_manager::metal_block_texture())
    {
    }
};
