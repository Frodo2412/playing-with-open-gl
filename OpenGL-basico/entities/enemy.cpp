#include "enemy.h"
#include <random>
#include "../interfaces/gamehud.h"

int enemy::get_new_direction()
{
    // Create a random device and use it to seed the random engine
    std::random_device rd;
    std::mt19937 gen(rd());

    // Create a uniform distribution from 1 to 4
    std::uniform_int_distribution<> distrib(1, 4);

    // Generate and print a random integer from the distribution
    return distrib(gen);
}

void enemy::handle_collision(game_object* other)
{
    const auto new_direction = get_new_direction();

    position_ -= speed_;

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
}

void enemy::destroy()
{
    is_active_ = false;
    gamehud::update_points(15);
}

bool enemy::is_active() const
{
    return is_active_;
}
