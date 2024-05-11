#pragma once
#include "../textures/texture_loader.h"

class number
{
    static number* numero;
    
    const texture one_instance_;
    const texture two_instance_;
    const texture three_instance_;
    const texture four_instance_;
    const texture five_instance_;
    const texture six_instance_;
    const texture seven_instance_;
    const texture eight_instance_;
    const texture nine_instance_;
    const texture zero_instance_;
    const texture gamehud_instance_;

    explicit number() : one_instance_(texture_loader::load_texture("../assets/textures/numbers/uno.png")),
        two_instance_(texture_loader::load_texture("../assets/textures/numbers/dos.png")),
        three_instance_(texture_loader::load_texture("../assets/textures/numbers/tres.png")),
        four_instance_(texture_loader::load_texture("../assets/textures/numbers/cuatro.png")),
        five_instance_(texture_loader::load_texture("../assets/textures/numbers/cinco.png")),
        six_instance_(texture_loader::load_texture("../assets/textures/numbers/seis.png")),
        seven_instance_(texture_loader::load_texture("../assets/textures/numbers/siete.png")),
        eight_instance_(texture_loader::load_texture("../assets/textures/numbers/ocho.png")),
        nine_instance_(texture_loader::load_texture("../assets/textures/numbers/nueve.png")),
        zero_instance_(texture_loader::load_texture("../assets/textures/numbers/cero.png")),
        gamehud_instance_(texture_loader::load_texture("../assets/textures/gamehud.jpg"))
    {
    }


public: 
    static void init();

    const static texture get_texture_zero();
    const static texture get_texture_one();
    const static texture get_texture_two();
    const static texture get_texture_three();
    const static texture get_texture_four();
    const static texture get_texture_five();
    const static texture get_texture_six();
    const static texture get_texture_seven();
    const static texture get_texture_eight();
    const static texture get_texture_nine();
    const static texture get_texture_gamehud();
};