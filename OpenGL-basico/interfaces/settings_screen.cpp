#include "settings_screen.h"

texture settings_screen::background_image_ = texture_loader::load_texture("../assets/textures/settings/ajustes.jpg");

settings_screen::settings_screen(const int win_width, const int win_height)
{
    float enabled_coord_x = (float)win_width / 2 - (float)(win_width * 0.28125);
    float enabled_coord_y = (float)win_height / 2 - (float)(win_height * 0.322917) + (float)((win_height - 480) * 0.05);
    enabled_coord_x = enabled_coord_x - 25;

    speed_button_ = speed_button(vector2(enabled_coord_x, enabled_coord_y),
                                 vector2(enabled_coord_x + 100, enabled_coord_y + 50));

    wireframe_checkbox_ = wireframe_checkbox(vector2(enabled_coord_x, enabled_coord_y),
                                             vector2(enabled_coord_x + 50, enabled_coord_y + 50));

    enabled_coord_y = enabled_coord_y - (float)(win_height * 0.15);


    texturas_checkbox_ = texturas_checkbox(vector2(enabled_coord_x, enabled_coord_y),
                                           vector2(enabled_coord_x + 50, enabled_coord_y + 50));

    enabled_coord_y = enabled_coord_y - (float)(win_height * 0.15);

    facetado_checkbox_ = facetado_checkbox(vector2(enabled_coord_x, enabled_coord_y),
                                           vector2(enabled_coord_x + 50, enabled_coord_y + 50));

    enabled_coord_x = enabled_coord_x - 25;
    enabled_coord_y = enabled_coord_y - (float)(win_height * 0.15);

    lights_button_ = lights_button(vector2(enabled_coord_x, enabled_coord_y),
                                   vector2(enabled_coord_x + 100, enabled_coord_y + 50));
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

GLuint settings_screen::get_background_texture_id()
{
    return background_image_.get_texture_id();
}
