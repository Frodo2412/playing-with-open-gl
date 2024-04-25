#pragma once
#include "button.h"
#include "../../interfaces/settings.h"
#include "../../textures/texture_loader.h"

class speed_button final : public button
{
    texture slow_button_texture_, normal_button_texture_, fast_button_texture_;

public:
    explicit speed_button(const vector2& top_left, const vector2& bottom_right)
        : button(top_left, bottom_right),
          slow_button_texture_(texture_loader::load_texture("../assets/textures/settings/slow.jpg")),
          normal_button_texture_(texture_loader::load_texture("../assets/textures/settings/normal.jpg")),
          fast_button_texture_(texture_loader::load_texture("../assets/textures/settings/fast.jpg"))
    {
    }

    speed_button(): slow_button_texture_(texture_loader::load_texture("../assets/textures/settings/slow.jpg")),
                    normal_button_texture_(texture_loader::load_texture("../assets/textures/settings/normal.jpg")),
                    fast_button_texture_(texture_loader::load_texture("../assets/textures/settings/fast.jpg"))
    {
    }

    GLuint get_texture_id() const override;
};
