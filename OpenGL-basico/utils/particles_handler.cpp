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

void particles_handler::update(int number_of_frame)
{
    auto it = particles_.begin();
    while (it != particles_.end())
    {
        particle* particle_pointer = *it;
        particle_pointer->update(number_of_frame);
        if (number_of_frame >= particle_pointer->get_life_time_in_frames_())
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

void particles_handler::add(int number_of_frame, vector3 position, vector3 velocity, vector4 initial_color, vector4 final_color, int life_time_in_frames)
{
    particles_.push_back(new particle(position, velocity, initial_color, final_color, life_time_in_frames + number_of_frame));
}

std::vector<particle*> particles_handler::get_particles()
{
    return particles_;
}
