#include "game_object.h"

vector3 game_object::get_position() const
{
    return position_;
}

texture game_object::get_texture() const
{
    return texture_;
}
