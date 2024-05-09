#include "particles_handler.h"

particles_handler* particles_handler::instance = nullptr;

particles_handler::particles_handler()
{
}

particles_handler* particles_handler::get_instance()
{
    if (instance == nullptr)
    {
        instance = new particles_handler();
    }
    return instance;
}

void particles_handler::update(int seconds)
{
    auto it = particles_.begin();
    while (it != particles_.end())
    {
        particle* particle_pointer = *it;
        particle_pointer->update(seconds);
        if (seconds >= particle_pointer->get_life_time_())
        {
            delete particle_pointer;
            it = particles_.erase(it);
            printf("PARTICULA BORRADA\n");
        }
        else
        {
            ++it;
        }
    }
}

void particles_handler::add(int seconds, vector3 position, vector3 velocity, vector4 initial_color, vector4 final_color, int size, int life_time)
{
    particles_.push_back(new particle(position, velocity, initial_color, final_color, size, life_time + seconds));
}

std::vector<particle*> particles_handler::get_particles()
{
    return particles_;
}

void particles_handler::create_explotion(int seconds, vector3 position, int number_of_particles)
{
    for (int i = 0; i < number_of_particles; i++)
    {
        vector3 velocity = vector3((rand() % 50) - 25, (rand() % 50) - 25, (rand() % 50) - 25);
        vector4 initial_color = vector4(1, 0, 0, 1);
        vector4 final_color = vector4(1, 1, 0, 0);
        add(seconds, position, velocity, initial_color, final_color, rand() % 10, 2);
    }
}
