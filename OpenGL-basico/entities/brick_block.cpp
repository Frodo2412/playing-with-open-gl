#include "brick_block.h"

void brick_block::destruir()
{
    this->active_ = false; // la bomba pasa a estar inactiva.
}

const texture brick_block::get_texture()
{
    return texture_;
}