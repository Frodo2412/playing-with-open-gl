#include "pedestal.h"


void pedestal::handle_collision(game_object* other)
{
    level_completed();
}

aabb pedestal::get_bounding_box() const
{
    const vector3 half_extents(0.20, 0.20, 0.20);
    return {position_ - half_extents, position_ + half_extents};
}

bool pedestal::get_is_level_completed()
{
    return is_level_completed_;
}

void pedestal::level_completed()
{
    is_level_completed_ = true;
}
