#pragma once
#include "block.h"
#include "../textures/texture_manager.h"

class brick_block final : public block
{
    bool active_;

public:
    explicit brick_block(const vector3& pos): block(pos, texture_manager::brick_block_texture()), active_(true)
    {
    }

    bool is_active() const override;
    bool is_destructible() const override;
    
    void destroy() override;
};
