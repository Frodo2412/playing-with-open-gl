#include "player.h"

void player::handle_collision(game_object* other)
{
    position_ -= speed_;
    speed_ = vector3::zero();
}

vector3 player::get_speed() const
{
    return speed_;
}
