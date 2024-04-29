#pragma once
#include "game_object.h"
#include "../geometry/vector3.h"
#include "../geometry/cube.h"
#include "../textures/texture_loader.h"

class block : public game_object
{
    cube cube_;
    float size_;

protected:
    explicit block(const vector3& position, const texture texture, const float size = 1.0):
        game_object(position, texture), cube_(cube(size, position)), size_(size)
    {
    }

public:
    virtual ~block() = default;

    cube get_block() const;
    virtual bool is_active() const = 0;
    virtual bool is_destructible() const = 0;

    aabb get_bounding_box() const override;
};
