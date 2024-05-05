#include "brick_block.h"
#include "../interfaces/gamehud.h"

bool brick_block::is_active() const
{
    return active_;
}

bool brick_block::is_destructible() const
{
    return true;
}

void brick_block::destroy()
{
    this->active_ = false; // la bomba pasa a estar inactiva.
    gamehud::update_points(10);
}
