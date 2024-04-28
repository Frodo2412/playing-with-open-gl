#pragma once
#include "block.h"
#include "../textures/texture_manager.h"

class brick_block : public block
{
    bool destructible_ = true;

public:
    explicit brick_block(const vector3& pos): block(pos, texture_manager::brick_block_texture())
    {
    }

    void destruir();
};
