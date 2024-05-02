#include "enemy.h"

void enemy::handle_collision(game_object* other)
{
}

void enemy::destroy()
{
    is_active_ = false;
}

bool enemy::is_active() const
{
    return is_active_;
}
