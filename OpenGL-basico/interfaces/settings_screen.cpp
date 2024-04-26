#include "settings_screen.h"

#include <iostream>

settings_screen::settings_screen(const int window_width, const int window_height): background_image_(
    texture_loader::load_texture("../assets/textures/settings/ajustes.jpg"))
{
    float enabled_coord_x = static_cast<float>(window_width) / 2 - static_cast<float>(window_width * 0.28125);
    float enabled_coord_y = static_cast<float>(window_height) / 2 - static_cast<float>(window_height * 0.322917) +
        static_cast<float>((window_height - 480) * 0.05);


    std::cout << "Speed button:\n" << "-Top left: " << enabled_coord_x << ", " << enabled_coord_y << '\n'
        << "-Bottom right: " << enabled_coord_x + 100 << ", " << enabled_coord_y + 50 << '\n';

    speed_button_ = speed_button(vector2(enabled_coord_x, enabled_coord_y),
                                 vector2(enabled_coord_x + 100, enabled_coord_y + 50));

    wireframe_checkbox_ = wireframe_checkbox(vector2(enabled_coord_x, enabled_coord_y),
                                             vector2(enabled_coord_x + 50, enabled_coord_y + 50));

    enabled_coord_y = enabled_coord_y - static_cast<float>(window_height * 0.15);

    std::cout << "Texturas checkbox:\n" << "-Top left: " << enabled_coord_x << ", " << enabled_coord_y << '\n'
        << "-Bottom right: " << enabled_coord_x + 50 << ", " << enabled_coord_y + 50 << '\n';

    texturas_checkbox_ = texturas_checkbox(vector2(enabled_coord_x, enabled_coord_y),
                                           vector2(enabled_coord_x + 50, enabled_coord_y + 50));

    enabled_coord_y = enabled_coord_y - static_cast<float>(window_height * 0.15);

    std::cout << "Facetado checkbox:\n" << "-Top left: " << enabled_coord_x << ", " << enabled_coord_y << '\n'
        << "-Bottom right: " << enabled_coord_x + 50 << ", " << enabled_coord_y + 50 << '\n';
    facetado_checkbox_ = facetado_checkbox(vector2(enabled_coord_x, enabled_coord_y),
                                           vector2(enabled_coord_x + 50, enabled_coord_y + 50));

    enabled_coord_x = enabled_coord_x - 25;
    enabled_coord_y = enabled_coord_y - static_cast<float>(window_height * 0.15);

    std::cout << "Lights button:\n" << "-Top left: " << enabled_coord_x << ", " << enabled_coord_y << '\n'
        << "-Bottom right: " << enabled_coord_x + 100 << ", " << enabled_coord_y + 50 << '\n';
    lights_button_ = lights_button(vector2(enabled_coord_x - 25, enabled_coord_y),
                                   vector2(enabled_coord_x + 75, enabled_coord_y + 50));
}

std::array<button*, 5> settings_screen::get_buttons()
{
    return {&speed_button_, &wireframe_checkbox_, &facetado_checkbox_, &texturas_checkbox_, &lights_button_};
}

void settings_screen::handle_click(const int x, const int y)
{
    for (const auto button : get_buttons())
        if (button->is_inside(x, y))
            button->on_click();
}

GLuint settings_screen::get_background_texture_id() const
{
    return background_image_.get_texture_id();
}
