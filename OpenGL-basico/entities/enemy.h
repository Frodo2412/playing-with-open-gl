#pragma once
#include "entity.h"
#include "../textures/texture_manager.h"

class enemy final : public entity
{
    bool is_active_;
public:
    explicit enemy(): entity("../assets/models/spider.obj", texture_manager::enemy_texture(), 1)
    {
    }

    void handle_collision(game_object* other) override;
    void destroy();
    bool is_active() const;
};
