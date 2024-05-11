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
                                            timer_(bomb_duration),
                                            exploded_(false)
    {
        position_ = position;
        position_.set_y(-0.5);
        is_player_ = false;
    }

    void explotar();
    bool is_exploded() const;
    float get_timer() const;
    void set_timer(float timer);

    void handle_collision(game_object* other) override;

    /**
     * The duration of the timer that makes the bomb go off in milliseconds.
     */
    static float const bomb_duration;
    static int const radius;
};
