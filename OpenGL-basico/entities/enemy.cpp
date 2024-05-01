#include "enemy.h"

void enemy::destroy()
{
    active_ = false;
}

const bool enemy::is_active()
{
    return active_;
}