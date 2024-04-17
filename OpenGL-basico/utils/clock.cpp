#include "clock.h"

clock* clock::instance_ = nullptr;

void clock::init()
{
    instance_ = new clock();
}

void clock::toggle_pause()
{
    instance_->is_pause_ = !(instance_->is_pause_);
}

double clock::get_ticks()
{
    const double current_time = SDL_GetTicks();
    double delta_time = current_time - instance_->start_time_;
    instance_->start_time_ = current_time;

    if (instance_->is_pause_)
        delta_time = 0;
    return delta_time;
}

void clock::reset()
{
    instance_->start_time_ = SDL_GetTicks();
}

Uint32 clock::get_total_time()
{
    double current_time = SDL_GetTicks(); // tiempo actual
    
    if (instance_->is_pause_) // Pausa
    {
        return instance_->total_elapsed_time_;
    }
    else
    {
        double elapsed_time = current_time - instance_->start_time_;
        instance_->total_elapsed_time_ = static_cast<Uint32>(elapsed_time);

        return instance_->total_elapsed_time_;
    }
}
