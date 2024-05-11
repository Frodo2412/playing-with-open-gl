#pragma once
#include "game_object.h"
#include "../geometry/vector3.h"
#include "../geometry/cube.h"
#include "../textures/texture_loader.h"

class block : public game_object
{
    cube cube_;

protected:
    explicit block(const vector3& position, const texture texture):
        game_object(position, texture), cube_(cube(block_size, position))
    {
    }

public:
    virtual ~block() = default;

    cube get_block() const;
    virtual bool is_destructible() const = 0;

    aabb get_bounding_box() const override;

    const static float block_size;
};
