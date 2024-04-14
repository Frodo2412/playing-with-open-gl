#include "clock.h"

clock* clock::instance_ = nullptr;

void clock::init()
{
    instance_ = new clock();
}

double clock::get_ticks()
{
    const double current_time = SDL_GetTicks();
    const double delta_time = current_time - instance_->start_time_;
    instance_->start_time_ = current_time;
    return delta_time;
}

void clock::reset()
{
    instance_->start_time_ = SDL_GetTicks();
}
