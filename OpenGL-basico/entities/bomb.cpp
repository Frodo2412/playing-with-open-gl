#include "bomb.h"

#include "brick_block.h"
#include "../utils/particles_handler.h"
#include "../utils/clock.h"

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

bool bomb::is_active() const
{
    return !exploded_;
}

void bomb::destroy()
{
}

void bomb::explotar()
{
    const auto clock = ::clock::get_instance();
    particles_handler* particles_handler = particles_handler::get_instance();
    particles_handler->create_explotion(clock->get_total_time() / 1000, position_, 128);
    exploded_ = true;
};
