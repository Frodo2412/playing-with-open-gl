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
    bool active_ = true;
    bool destructible_ = true;

public:
    explicit block(const vector3& position, const texture texture, const float size = 1.0):
        game_object(position, texture), cube_(cube(size, position)), size_(size)
    {
    }

    virtual ~block() = default;

    cube get_block() const;
    bool is_active();
    float get_size();
    
    aabb get_bounding_box() override;
};
