#pragma once
#include "button.h"
#include "../../textures/texture_loader.h"

class lights_button final : public button
{
    texture day_texture_, night_texture_, red_texture_, green_texture_, blue_texture_;

public:
    explicit lights_button(const vector2& top_left, const vector2& bottom_right): button(top_left, bottom_right),
        day_texture_(texture_loader::load_texture("../assets/textures/settings/dia.jpg")),
        night_texture_(texture_loader::load_texture("../assets/textures/settings/noche.jpg")),
        red_texture_(texture_loader::load_texture("../assets/textures/settings/rojo.jpg")),
        green_texture_(texture_loader::load_texture("../assets/textures/settings/verde.jpg")),
        blue_texture_(texture_loader::load_texture("../assets/textures/settings/azul.jpg"))
    {
    }

    lights_button()
        :
        day_texture_(texture_loader::load_texture("../assets/textures/settings/dia.jpg")),
        night_texture_(texture_loader::load_texture("../assets/textures/settings/noche.jpg")),
        red_texture_(texture_loader::load_texture("../assets/textures/settings/rojo.jpg")),
        green_texture_(texture_loader::load_texture("../assets/textures/settings/verde.jpg")),
        blue_texture_(texture_loader::load_texture("../assets/textures/settings/azul.jpg"))
    {
    }

    GLuint get_texture_id() const override;
};
