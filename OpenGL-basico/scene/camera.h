#pragma once
#include "../entities/player.h"
#include "../geometry/vector3.h"

class camera
{
    vector3 position_, direction_, up_;

public:
    explicit camera(const player* player)
        : position_(player->get_position()), direction_(player->get_direction()), up_(player->get_up())
    {
    }

    vector3 get_position() const;
    vector3 get_direction() const;
    vector3 get_up() const;

    void set_direction(const vector3& direction);
    void set_position(const vector3& position);
    void set_up(const vector3& up);

    void move(const vector3& displacement);
    void move(const player* player);
    void rotate(float x_offset, float y_offset);
};
