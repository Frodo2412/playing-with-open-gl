#pragma once
#include <SDL_timer.h>


class clock
{
    double start_time_;
    bool is_pause_ = false;
    static clock* instance_;

    explicit clock(): start_time_(SDL_GetTicks())
    {
    }

public:
    static void init();
    static double get_ticks();
    static void toggle_pause();
    static void reset();
    static Uint32 get_total_time();
    bool get_is_paused() const;
    static clock* get_instance();
};
