#include "player.h"

#include "../utils/game_over_exception.h"

void player::handle_collision(game_object* other)
{
    position_ -= speed_;
    speed_ = vector3::zero();
}

vector3 player::get_speed() const
{
    return speed_;
}

bool player::is_active() const
{
    return true;
}

void player::destroy()
{
    throw game_over_exception();
}
