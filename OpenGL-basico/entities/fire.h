#pragma once
#include "entity.h"
#include "../textures/texture_manager.h"

class fire final : public entity
{
    bool is_active_ = true;

public:
    explicit fire(vector3 position): entity("../assets/models/fire.obj",
                                            texture_manager::fire_texture(), 1,
                                            position)
    {
    }

    void handle_collision(game_object* other) override;
    fire spread(const vector3& direction);

    void destroy() override;
    aabb get_bounding_box() const override;
    bool is_active() const override;
};
