#pragma once
#include <array>

#include "../textures/texture.h"
#include "buttons/checkbox.h"
#include "buttons/lights_button.h"
#include "buttons/speed_button.h"

class settings_screen
{
    speed_button speed_button_;
    wireframe_checkbox wireframe_checkbox_;
    facetado_checkbox facetado_checkbox_;
    texturas_checkbox texturas_checkbox_;
    lights_button lights_button_;
    texture background_image_;

public:
    explicit settings_screen(const int window_width, const int window_height);

    std::array<button*, 5> get_buttons();
    void handle_click(int x, int y);
    GLuint get_background_texture_id() const;
};
