#pragma once
#include "block.h"
#include "../geometry/vector3.h"


class metal_block final: public block
{
    bool is_active_;

public:
    explicit metal_block(const vector3& pos, float size): block(pos, size, block::metal_texture), is_active_(true) {}
       
    bool is_destroyable() override;
    bool is_active() override;
    void destroy() override;
};