#include "particle.h"

particle::particle(vector3 position, vector3 velocity, vector4 initial_color, vector4 final_color, int life_time_in_frames)
    : position_(position), velocity_(velocity), initial_color_(initial_color), final_color_(final_color), color_(initial_color), life_time_in_frames_(life_time_in_frames)
{
}

void particle::set_position(vector3 position)
{
    position_ = position;
}

void particle::set_velocity(vector3 velocity)
{
    velocity_ = velocity;
}

vector3 particle::get_position()
{
    return position_;
}

vector3 particle::get_velocity()
{
    return velocity_;
}

void particle::set_initial_color(vector4 color)
{
    initial_color_ = color;
}

void particle::set_final_color(vector4 color)
{
    final_color_ = color;
}

vector4 particle::get_initial_color()
{
    return initial_color_;
}

vector4 particle::get_final_color()
{
    return final_color_;
}

void particle::set_life_time_in_frames_(int life_time)
{
    life_time_in_frames_ = life_time;
}

int particle::get_life_time_in_frames_()
{
    return life_time_in_frames_;
}

vector4 particle::get_color()
{
    return color_;
}

void particle::update(int number_of_frame)
{
    if (life_time_in_frames_ - number_of_frame >= 0)
    {
        position_ += velocity_*0.01;//SE VA DESACELERANDO
        float r = (initial_color_.get_r()*((float)life_time_in_frames_ - (float)number_of_frame) + final_color_.get_r()*(float)number_of_frame)/(float)life_time_in_frames_;
        float g = (initial_color_.get_g()*((float)life_time_in_frames_ - (float)number_of_frame) + final_color_.get_g()*(float)number_of_frame)/(float)life_time_in_frames_;
        float b = (initial_color_.get_b()*((float)life_time_in_frames_ - (float)number_of_frame) + final_color_.get_b()*(float)number_of_frame)/(float)life_time_in_frames_;
        float alpha = (initial_color_.get_alpha()*((float)life_time_in_frames_ - (float)number_of_frame) + final_color_.get_alpha()*(float)number_of_frame)/(float)life_time_in_frames_;
        color_.set_r(r);
        color_.set_g(g);
        color_.set_b(b);
        color_.set_alpha(alpha);
    }
}