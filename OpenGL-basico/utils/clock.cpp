#include "clock.h"

clock* clock::instance_ = nullptr;

void clock::init()
{
    instance_ = new clock();
}

void clock::toggle_pause()
{
    instance_->is_pause_ = !instance_->is_pause_;
}


double clock::get_ticks()
{
    const double current_time = SDL_GetTicks();
    double delta_time = current_time - instance_->start_time_;
    instance_->start_time_ = current_time;

    if (instance_->is_pause_)
        delta_time = 0;
    instance_->played_time_ = delta_time + instance_->played_time_;
    return delta_time;
}

void clock::reset()
{
    instance_->start_time_ = SDL_GetTicks();
    instance_->played_time_ = 0;
}

Uint32 clock::get_total_time()
{
    return instance_->played_time_;
}

bool clock::get_is_paused() const
{
    return is_pause_;
}

clock* clock::get_instance()
{
    if (instance_ == nullptr)
        instance_ = new clock();
    return instance_;
}
