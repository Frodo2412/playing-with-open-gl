#pragma once
#include "../geometry/vector3.h"
#include "../geometry/vector4.h"


class particle
{
private:
    vector3 position_;
    vector3 velocity_;
    vector4 initial_color_;
    vector4 final_color_;
    vector4 color_;
    int life_time_in_frames_;
    
public:
    particle(vector3 position, vector3 velocity, vector4 initial_color, vector4 final_color, int life_time);
    void set_position(vector3 position);
    void set_velocity(vector3 velocity);
    void set_initial_color(vector4 color);
    void set_final_color(vector4 color);
    void set_life_time_in_frames_(int life_time);
    vector3 get_position();
    vector3 get_velocity();
    vector4 get_initial_color();
    vector4 get_final_color();
    vector4 get_color();
    int get_life_time_in_frames_();
    void update(int number_of_frame);
};
