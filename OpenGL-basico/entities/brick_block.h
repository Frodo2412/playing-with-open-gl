#pragma once
#include "block.h"

class brick_block : public block
{
   bool is_active_;

public:
   explicit brick_block(const vector3& pos, float size): block(pos, size, block::brick_texture), is_active_(true) {}
       
   bool is_destroyable() override;
   bool is_active() override;
   void destroy() override;
};