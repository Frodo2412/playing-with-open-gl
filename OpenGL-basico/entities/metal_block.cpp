#include "metal_block.h"

bool metal_block::is_active() const
{
    return true;
}

bool metal_block::is_destructible() const
{
    return false;
}

void metal_block::destroy()
{
}
