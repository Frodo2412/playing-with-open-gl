#include "metal_block.h"

bool metal_block::is_destroyable()
{
    return false;
}

bool metal_block::is_active()
{
    return is_active_;
}

void metal_block::destroy()
{
}