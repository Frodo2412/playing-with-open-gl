#include "brick_block.h"

#include <iostream>

bool brick_block::is_destroyable()
{
    return true;
}

bool brick_block::is_active()
{
    return is_active_;
}

void brick_block::destroy()
{
    is_active_ = false;
    std::cout<< "Block destroyed" << "\n";
}