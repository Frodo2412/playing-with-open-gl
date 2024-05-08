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
    for (particle* particle_pointer : particles_)
    {
        particle_pointer->update(number_of_frame);
        if (number_of_frame >= particle_pointer->get_life_time_in_frames_())//SI YA SE TERMINO EL LIFE_TIME DE LA PARTICULA LA BORRO
        {
            particles_.erase(std::remove(particles_.begin(), particles_.end(), particle_pointer), particles_.end());
            delete particle_pointer;
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
