#pragma once
#include "../geometry/vector3.h"

class camera
{
    vector3 position_, direction_, up_;

public:
    explicit camera(const vector3& position, const vector3& direction, const vector3& up)
        : position_(position), direction_(direction), up_(up)
    {
    }

    explicit camera(const float x, const float y, const float z)
        : position_(vector3(x, y, z)), direction_(vector3(0, 0, 0)), up_(vector3(0, 1, 0))
    {
    }

    vector3 get_position() const;
    vector3 get_direction() const;
    vector3 get_up() const;

    void move(const vector3& displacement);

    void zoom_in(float amount);
    void zoom_out(float amount);
    
    void rotate(float x_offset, float y_offset);

    void refresh() const;
    
};
