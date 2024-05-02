#pragma once
#include "block.h"
#include "../geometry/vector3.h"
#include "../textures/texture_manager.h"

class metal_block final : public block
{
public:
    explicit metal_block(const vector3& position): block(position, texture_manager::metal_block_texture())
    {
    }

    bool is_active() const override;
    bool is_destructible() const override;
    void destroy() override;
};
