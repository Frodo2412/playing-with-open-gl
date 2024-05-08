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
    float remaining_frames = (float)(life_time_in_frames_ - number_of_frame);
    if (remaining_frames >= 0)
    {
        position_ += velocity_ * remaining_frames * 0.00001;//SE VA DESACELERANDO POR REMAINING_FRAMES
        float r = initial_color_.get_r()*remaining_frames/(float)life_time_in_frames_ + final_color_.get_r()*(float)number_of_frame/(float)life_time_in_frames_;
        float g = initial_color_.get_g()*remaining_frames/(float)life_time_in_frames_ + final_color_.get_g()*(float)number_of_frame/(float)life_time_in_frames_;
        float b = initial_color_.get_b()*remaining_frames/(float)life_time_in_frames_ + final_color_.get_b()*(float)number_of_frame/(float)life_time_in_frames_;
        float alpha = initial_color_.get_alpha()*remaining_frames/(float)life_time_in_frames_ + final_color_.get_alpha()*(float)number_of_frame/(float)life_time_in_frames_;
        color_.set_r(r);
        color_.set_g(g);
        color_.set_b(g);
        color_.set_alpha(alpha);
    }
}

particle::~particle()
{
}