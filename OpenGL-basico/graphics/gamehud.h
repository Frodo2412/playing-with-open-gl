#pragma once

#include <SDL_stdinc.h>
#include <iostream>
#include "../geometry/square.h"

class gamehud
{
    square contenedor_ = square(vector3(-0.8f, -0.9f, 0.0f), vector3(0.8f, -0.9f, 0.0f), vector3(0.8f, -0.6f, 0.0f), vector3(-0.8f, -0.6f, 0.0f));
    square score_ = square(vector3(-0.75f, -0.75f, 0.0f), vector3(-0.5f, -0.75f, 0.0f), vector3(-0.5f, -0.85f, 0.0f), vector3(-0.75f, -0.85f, 0.0f));
    square tiempo_ = square(vector3(-0.1f, -0.62f, 0.0f), vector3(0.1f, -0.62f, 0.0f), vector3(0.1f, -0.68f, 0.0f), vector3(-0.1f, -0.68f, 0.0f));
    
    square minutos_decena_ = square(vector3(-0.145f, -0.7f, 0.0f), vector3(-0.095f, -0.7f, 0.0f), vector3(-0.095f, -0.85f, 0.0f), vector3(-0.145f, -0.85f, 0.0f));
    square minutos_unidades_ = square(vector3(-0.085f, -0.7f, 0.0f), vector3(-0.035f, -0.7f, 0.0f), vector3(-0.035f, -0.85f, 0.0f), vector3(-0.085f, -0.85f, 0.0f));
    square espacio_ = square(vector3(-0.025f, -0.7f, 0.0f), vector3(0.025f, -0.7f, 0.0f), vector3(0.025f, -0.85f, 0.0f), vector3(-0.025f, -0.85f, 0.0f));
    square segundos_decena_ = square(vector3(0.035f, -0.7f, 0.0f), vector3(0.085f, -0.7f, 0.0f), vector3(0.085f, -0.85f, 0.0f), vector3(0.035f, -0.85f, 0.0f));
    square segundos_unidades_ = square(vector3(0.095f, -0.7f, 0.0f), vector3(0.145f, -0.7f, 0.0f), vector3(0.145f, -0.85f, 0.0f), vector3(0.095f, -0.85f, 0.0f));
    
public:
    explicit gamehud();
    void drop_time(Uint32 milisecond);
    void cambiar_numero(Uint32 valor, square ubicacion);
};