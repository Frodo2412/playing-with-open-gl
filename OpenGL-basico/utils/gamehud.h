#pragma once

#include <SDL_stdinc.h>
#include <iostream>
#include "../geometry/square.h"

class gamehud
{
    square contenedor_ = square(vector(-0.8, -0.9, 0.0), vector(0.8, -0.9, 0.0), vector(0.8, -0.6, 0.0), vector(-0.8, -0.6, 0.0));
    square tiempo_ = square(vector( -0.75, -0.75, 0.0), vector(-0.5, -0.75, 0.0), vector(-0.5, -0.85, 0.0), vector(- 0.75, -0.85, 0.0));
    square score_ = square(vector( -0.1, -0.62, 0.0), vector(0.1, -0.62, 0.0), vector(0.1, -0.68, 0.0), vector(- 0.1, -0.68, 0.0));
    
    square minutos_decena_ = square(vector(-0.195 + 0.05, -0.7, 0.0), vector(-0.145 + 0.05, -0.7, 0.0), vector(-0.145 + 0.05, -0.85, 0.0), vector(-0.195 + 0.05, -0.85, 0.0));
    square minutos_unidades_ = square(vector(-0.135 + 0.05, -0.7, 0.0), vector(-0.085 + 0.05, -0.7, 0.0), vector(-0.085 + 0.05, -0.85, 0.0), vector(-0.135 + 0.05, -0.85, 0.0));
    square espacio_ = square(vector(-0.075 + 0.05, -0.7, 0.0), vector(-0.025 + 0.05, -0.7, 0.0), vector(-0.025 + 0.05, -0.85, 0.0), vector(-0.075 + 0.05, -0.85, 0.0));
    square segundos_decena_ = square(vector(-0.015 + 0.05, -0.7, 0.0), vector(0.035 + 0.05, -0.7, 0.0), vector(0.035 + 0.05, -0.85, 0.0), vector(-0.015 + 0.05, -0.85, 0.0));
    square segundos_unidades_ = square(vector(0.045 + 0.05, -0.7, 0.0), vector(0.095 + 0.05, -0.7, 0.0), vector(0.095 + 0.05, -0.85, 0.0), vector(0.045 + 0.05, -0.85, 0.0));


public:
    explicit gamehud();
    void drop_time(Uint32 milisecond);
    
};