#pragma once

#include "entity.h"
#include "block.h"
#include "enemy.h"

class bomb final : public entity
{
    float timer_;
    bool exploded_;

public:
    explicit bomb(const vector3& position): entity("../assets/models/Bomb.obj", texture_manager::bomb_texture(), 1),
                                            timer_(5),
                                            exploded_(false)
    {
        position_ = position;
    }

    void explotar();
    bool is_exploded() const;
    float get_timer() const;
    void set_timer(float timer);

    void handle_collision(game_object* other) override;
};
