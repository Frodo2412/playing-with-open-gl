#pragma once
#include "../geometry/vector.h"

class camera
{
    vector position_, direction_, up_;

public:
    explicit camera(const vector& position, const vector& direction, const vector& up)
        : position_(position), direction_(direction), up_(up)
    {
    }

    explicit camera(const float x, const float y, const float z)
        : position_(vector(x, y, z)), direction_(vector(0, 0, 0)), up_(vector(0, 1, 0))
    {
    }

    vector get_position() const;
    vector get_direction() const;
    vector get_up() const;

    void zoom_in(float amount);
    void zoom_out(float amount);
};
