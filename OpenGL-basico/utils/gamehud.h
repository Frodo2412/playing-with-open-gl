#pragma once

#include <SDL_stdinc.h>
#include <iostream>
#include "../geometry/square.h"
#include "../textures/texture_loader.h"

class gamehud
{
    square contenedor_ = square(vector(-0.8f, -0.9f, 0.0f), vector(0.8f, -0.9f, 0.0f), vector(0.8f, -0.6f, 0.0f), vector(-0.8f, -0.6f, 0.0f));
    square tiempo_ = square(vector(-0.75f, -0.75f, 0.0f), vector(-0.5f, -0.75f, 0.0f), vector(-0.5f, -0.85f, 0.0f), vector(-0.75f, -0.85f, 0.0f));
    square score_ = square(vector(-0.1f, -0.62f, 0.0f), vector(0.1f, -0.62f, 0.0f), vector(0.1f, -0.68f, 0.0f), vector(-0.1f, -0.68f, 0.0f));
    
    square minutos_decena_ = square(vector(-0.145f, -0.7f, 0.0f), vector(-0.095f, -0.7f, 0.0f), vector(-0.095f, -0.85f, 0.0f), vector(-0.145f, -0.85f, 0.0f));
    square minutos_unidades_ = square(vector(-0.085f, -0.7f, 0.0f), vector(-0.035f, -0.7f, 0.0f), vector(-0.035f, -0.85f, 0.0f), vector(-0.085f, -0.85f, 0.0f));
    square espacio_ = square(vector(-0.025f, -0.7f, 0.0f), vector(0.025f, -0.7f, 0.0f), vector(0.025f, -0.85f, 0.0f), vector(-0.025f, -0.85f, 0.0f));
    square segundos_decena_ = square(vector(0.035f, -0.7f, 0.0f), vector(0.085f, -0.7f, 0.0f), vector(0.085f, -0.85f, 0.0f), vector(0.035f, -0.85f, 0.0f));
    square segundos_unidades_ = square(vector(0.095f, -0.7f, 0.0f), vector(0.145f, -0.7f, 0.0f), vector(0.145f, -0.85f, 0.0f), vector(0.095f, -0.85f, 0.0f));
    const texture two_dots_;
    const texture cero_;
    const texture uno_;
    const texture dos_;
    const texture tres_;
    const texture cuatro_;
    const texture cinco_;
    const texture seis_;
    const texture siete_;
    const texture ocho_;
    const texture nueve_;
public:
    explicit gamehud() : two_dots_(texture_loader::load_texture("../assets/two_dots.jpg")),
                        cero_(texture_loader::load_texture("../assets/numbers/cero.png")),
                        uno_(texture_loader::load_texture("../assets/numbers/uno.png")),
                        dos_(texture_loader::load_texture("../assets/numbers/dos.png")),
                        tres_(texture_loader::load_texture("../assets/numbers/tres.png")),
                        cuatro_(texture_loader::load_texture("../assets/numbers/cuatro.png")),
                        cinco_(texture_loader::load_texture("../assets/numbers/cinco.png")),
                        seis_(texture_loader::load_texture("../assets/numbers/seis.png")),
                        siete_(texture_loader::load_texture("../assets/numbers/siete.png")),
                        ocho_(texture_loader::load_texture("../assets/numbers/ocho.png")),
                        nueve_(texture_loader::load_texture("../assets/numbers/nueve.png")) {};
    void drop_time(Uint32 milisecond);
    
};