#include "brick_block.h"

void brick_block::destruir()
{
    this->active_ = false; // la bomba pasa a estar inactiva.
}

bool brick_block::is_active() const
{
    return active_;
}

bool brick_block::is_destructible() const
{
    return true;
}
