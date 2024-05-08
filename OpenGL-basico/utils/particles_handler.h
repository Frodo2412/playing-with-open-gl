#pragma once
#include <vector>

#include "../entities/particle.h"

class particles_handler
{
private:
    particles_handler();
    static particles_handler* instance;
    std::vector<particle*> particles_;
public:
    static particles_handler* get_instance();
    void update(int number_of_frame);
    void add(int number_of_frame, vector3 position, vector3 velocity, vector4 initial_color, vector4 final_color, int life_time_in_frames);
    std::vector<particle*> get_particles();//USAR DESPUES DE UPDATE!!!
};
