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
    void update(float seconds);
    void add(float seconds, vector3 position, vector3 velocity, vector4 initial_color, vector4 final_color, float size, float life_time);
    std::vector<particle*> get_particles();//USAR DESPUES DE UPDATE!!!
    void create_explotion(float seconds, vector3 position, int number_of_particles);
    void walk_particles(float seconds, vector3 position, vector3 speed, int number_of_particles);
};
