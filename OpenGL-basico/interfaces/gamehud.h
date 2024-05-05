#pragma once

#include <SDL_stdinc.h>
#include "../geometry/square.h"

class gamehud
{
    static gamehud* instance_;
    square contenedor_ = square(vector3(-0.8f, -0.9f, 0.0f), vector3(0.8f, -0.9f, 0.0f), vector3(0.8f, -0.6f, 0.0f), vector3(-0.8f, -0.6f, 0.0f));
    //square score_ = square(vector3(-0.75f, -0.75f, 0.0f), vector3(-0.5f, -0.75f, 0.0f), vector3(-0.5f, -0.85f, 0.0f), vector3(-0.75f, -0.85f, 0.0f));
    square tiempo_ = square(vector3(-0.1f, -0.62f, 0.0f), vector3(0.1f, -0.62f, 0.0f), vector3(0.1f, -0.68f, 0.0f), vector3(-0.1f, -0.68f, 0.0f));

    square minutos_decena_ = square(vector3(-0.145f, -0.7f, 0.0f), vector3(-0.095f, -0.7f, 0.0f), vector3(-0.095f, -0.85f, 0.0f), vector3(-0.145f, -0.85f, 0.0f));
    square minutos_unidades_ = square(vector3(-0.085f, -0.7f, 0.0f), vector3(-0.035f, -0.7f, 0.0f), vector3(-0.035f, -0.85f, 0.0f), vector3(-0.085f, -0.85f, 0.0f));
    square espacio_ = square(vector3(-0.025f, -0.7f, 0.0f), vector3(0.025f, -0.7f, 0.0f), vector3(0.025f, -0.85f, 0.0f), vector3(-0.025f, -0.85f, 0.0f));
    square segundos_decena_ = square(vector3(0.035f, -0.7f, 0.0f), vector3(0.085f, -0.7f, 0.0f), vector3(0.085f, -0.85f, 0.0f), vector3(0.035f, -0.85f, 0.0f));
    square segundos_unidades_ = square(vector3(0.095f, -0.7f, 0.0f), vector3(0.145f, -0.7f, 0.0f), vector3(0.145f, -0.85f, 0.0f), vector3(0.095f, -0.85f, 0.0f));

    Uint32 score_ = 0;
    square score_miles_ = square(vector3(-0.75f, -0.7f, 0.0f), vector3(-0.7f, -0.7f, 0.0f), vector3(-0.7f, -0.85f, 0.0f), vector3(-0.75f, -0.85f, 0.0f));
    square score_cientos_ = square(vector3(-0.69f, -0.7f, 0.0f), vector3(-0.64f, -0.7f, 0.0f), vector3(-0.64f, -0.85f, 0.0f) , vector3(-0.69f, -0.85f, 0.0f));
    square score_decenas_ = square(vector3(-0.63f, -0.7f, 0.0f), vector3(-0.58f, -0.7f, 0.0f), vector3(-0.58f, -0.85f, 0.0f), vector3(-0.63f, -0.85f, 0.0f));
    square score_unidades_ = square(vector3(-0.57f, -0.7f, 0.0f), vector3(-0.52f, -0.7f, 0.0f), vector3(-0.52f, -0.85f, 0.0f), vector3(-0.57f, -0.85f, 0.0f));
    explicit gamehud() = default;
    
public:
    
    static void init();
    static void draw_time(Uint32 millisecond);
    static void cambiar_numero(Uint32 valor, square ubicacion);
    static void update_points(Uint32 points);
};