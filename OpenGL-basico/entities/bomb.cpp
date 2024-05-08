#include "bomb.h"

#include "brick_block.h"
#include "metal_block.h"

constexpr float bomb::bomb_duration = 5000;
constexpr int bomb::radius = 3;

bool bomb::is_exploded() const
{
    return exploded_;
}

float bomb::get_timer() const
{
    return timer_;
}

void bomb::set_timer(const float timer)
{
    timer_ = timer;
}

void bomb::handle_collision(game_object* other)
{
}

void bomb::explotar()
{
    particles_handler* particles_handler = particles_handler::get_instance();
    particles_handler->create_explotion(0, position_, 32);
    exploded_ = true;
};
