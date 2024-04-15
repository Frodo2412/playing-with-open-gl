#pragma once
#include "../geometry/vertex.h"

class camera
{
    vertex position_, direction_, up_;

public:
    explicit camera(const vertex& position, const vertex& direction, const vertex& up)
        : position_(position), direction_(direction), up_(up)
    {
    }

    explicit camera(const float x, const float y, const float z)
        : position_(vertex(x, y, z)), direction_(vertex(0, 0, 0)), up_(vertex(0, 1, 0))
    {
    }

    vertex get_position() const;
    vertex get_direction() const;
    vertex get_up() const;

    void move(const vertex& displacement);

    void zoom_in(float amount);
    void zoom_out(float amount);
    
    void rotate(float x_offset, float y_offset);

    void refresh() const;
    
};
