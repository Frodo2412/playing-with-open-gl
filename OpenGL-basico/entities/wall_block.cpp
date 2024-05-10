#include "wall_block.h"

bool wall_block::is_active() const
{
    return true;
}

bool wall_block::is_destructible() const
{
    return false;
}

void wall_block::destroy()
{
}
