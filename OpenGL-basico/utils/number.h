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
    const texture two_dots_instance_;
    const texture gamehud_instance_;
    const texture time_instance_;

    explicit number() : one_instance_(texture_loader::load_texture("../assets/numbers/uno.png")),
        two_instance_(texture_loader::load_texture("../assets/numbers/dos.png")),
        three_instance_(texture_loader::load_texture("../assets/numbers/tres.png")),
        four_instance_(texture_loader::load_texture("../assets/numbers/cuatro.png")),
        five_instance_(texture_loader::load_texture("../assets/numbers/cinco.png")),
        six_instance_(texture_loader::load_texture("../assets/numbers/seis.png")),
        seven_instance_(texture_loader::load_texture("../assets/numbers/siete.png")),
        eight_instance_(texture_loader::load_texture("../assets/numbers/ocho.png")),
        nine_instance_(texture_loader::load_texture("../assets/numbers/nueve.png")),
        zero_instance_(texture_loader::load_texture("../assets/numbers/cero.png")),
        two_dots_instance_(texture_loader::load_texture("../assets/two_dots.jpg")),
        gamehud_instance_(texture_loader::load_texture("../assets/bricks_1.jpg")),
        time_instance_(texture_loader::load_texture("../assets/numbers/time.jpg"))
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
    const static texture get_two_dots();
    const static texture get_texture_gamehud();
    const static texture get_texture_time();
};