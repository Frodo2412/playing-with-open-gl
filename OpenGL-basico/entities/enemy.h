#pragma once
#include <random>

#include "entity.h"
#include "../textures/texture_manager.h"

class enemy final : public entity
{
    bool is_active_;

    static int get_new_direction();

public:
    explicit enemy(const vector3& position): entity("../assets/models/spider.obj", texture_manager::enemy_texture(), 0.9,
                                                    position + vector3(-0.1f, -0.3, 0.1f)), is_active_(true)
    {
        const auto new_direction = get_new_direction();

        switch (new_direction)
        {
        case 1:
            speed_ = vector3(0, 0, -0.05f);
            set_new_rotation(down);
            break;
        case 2:
            speed_ = vector3(0, 0, 0.05f);
            set_new_rotation(up);
            break;
        case 3:
            speed_ = vector3(-0.05f, 0, 0);
            set_new_rotation(right);
            break;
        case 4:
            speed_ = vector3(0.05f, 0, 0);
            set_new_rotation(left);
            break;
        default: break;
        }
        is_player_ = false;
    }

    void handle_collision(game_object* other) override;
    void destroy();
    bool is_active() const;
};
