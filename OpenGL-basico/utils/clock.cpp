#include "clock.h"

clock* clock::instance_ = nullptr;

void clock::init()
{
    instance_ = new clock();
}

void clock::toggle_pause()
{
    instance_->is_pause = !(instance_->is_pause);
}


double clock::get_ticks()
{
    const double current_time = SDL_GetTicks();
    double delta_time = current_time - instance_->start_time_;
    instance_->start_time_ = current_time;

    if (instance_->is_pause)
        delta_time = 0;
    return delta_time;
}

void clock::reset()
{
    instance_->start_time_ = SDL_GetTicks();
}
