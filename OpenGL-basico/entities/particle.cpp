#include "particle.h"

particle::particle(vector3 position, vector3 velocity, vector4 initial_color, vector4 final_color, float size, float life_time)
    : position_(position), velocity_(velocity), initial_color_(initial_color), final_color_(final_color), color_(initial_color), size_(size), life_time_(life_time)
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

void particle::set_life_time_(float life_time)
{
    life_time_ = life_time;
}

float particle::get_life_time_()
{
    return life_time_;
}

vector4 particle::get_color()
{
    return color_;
}

float particle::get_size()
{
    return size_;
}

void particle::set_size(float size)
{
    size_ = size;
}

void particle::update(float seconds, float game_velocity)
{
    const float remaining_time = (life_time_ - seconds);
    if (remaining_time >= 0)
    {
        position_ += velocity_ * game_velocity * remaining_time * 0.001;//SE VA DESACELERANDO POR REMAINING_time
       // const float r = initial_color_.get_r()*remaining_time/life_time_ + final_color_.get_r()*seconds/life_time_;
       // const float g = initial_color_.get_g()*remaining_time/life_time_ + final_color_.get_g()*seconds/life_time_;
       // const float b = initial_color_.get_b()*remaining_time/life_time_ + final_color_.get_b()*seconds/life_time_;
       // const float alpha = initial_color_.get_alpha()*remaining_time/life_time_ + final_color_.get_alpha()*seconds/life_time_;
        color_.set_r(1);
        color_.set_g(1);
        color_.set_b(1);
        color_.set_alpha(1);
        
    }
}
