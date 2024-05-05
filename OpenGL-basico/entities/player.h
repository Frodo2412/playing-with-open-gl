#pragma once
#include "entity.h"
#include "../textures/texture_manager.h"

class player final : public entity
{
public:
    explicit player(): entity("../assets/models/bomberman.obj", texture_manager::player_texture(), 1)
    {
    }

    void handle_collision(game_object* other) override;
    vector3& get_speed();
};
