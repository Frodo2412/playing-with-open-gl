#include "player.h"

void player::handle_collision(game_object* other)
{
    auto pedestal_obj = dynamic_cast<pedestal*>(other);
    if(pedestal_obj != nullptr)
    {
        pedestal_obj->level_completed();
    }else
    {
        position_ -= speed_;
        speed_ = vector3::zero();
    }
}

vector3 player::get_speed() const
{
    return speed_;
}
