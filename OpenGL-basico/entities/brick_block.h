#pragma once
#include "block.h"

class brick_block : public block
{
   texture texture_;
   bool destructible_ = true;
public:
   brick_block(const vector3& pos): block(pos), texture_(texture_loader::load_texture("../assets/textures/bricks_1.jpg") ) {};
   void destruir();
   const texture get_texture() override;
};
