#pragma once

#include "../geometry/vector3.h"
#include "../textures/texture.h"

struct aabb
{
    vector3 min;
    vector3 max;
};

class game_object
{
protected:
    vector3 position_;
    texture texture_;

    explicit game_object(const vector3& position, const texture texture): position_(position), texture_(texture)
    {
    }

    ~game_object() = default;

public:
    virtual aabb get_bounding_box() const = 0;
    vector3 get_position() const;
    texture get_texture() const;
};
