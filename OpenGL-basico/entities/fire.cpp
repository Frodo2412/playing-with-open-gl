#include "fire.h"

void fire::handle_collision(game_object* other)
{
    other->destroy();
}

fire fire::spread(const vector3& direction)
{
    destroy();
    return fire(position_ + direction, range_ - 1);
}

void fire::destroy()
{
}

aabb fire::get_bounding_box() const
{
    return entity::get_bounding_box();
}

bool fire::is_active() const
{
    return is_active_ && range_ > 0;
}
