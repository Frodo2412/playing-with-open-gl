#pragma once
#include <SDL_timer.h>


class clock
{
    double start_time_;
    static clock* instance_;

    explicit clock(): start_time_(SDL_GetTicks())
    {
    }

public:
    static void init();
    static double get_ticks();
    static void reset();
};
