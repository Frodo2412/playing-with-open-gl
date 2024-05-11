#pragma once
#include <random>

#include "entity.h"
#include "../textures/texture_manager.h"

class enemy final : public entity
{
    bool is_active_;

    static int get_new_direction();

public:
    explicit enemy(const vector3& position): entity("../assets/models/spider.obj", texture_manager::enemy_texture(), 1,
                                                    position), is_active_(true)
    {
        is_player_ = false;
    }

    void handle_collision(game_object* other) override;
    void destroy();
    bool is_active() const;
};
