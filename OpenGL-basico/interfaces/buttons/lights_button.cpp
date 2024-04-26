#include "lights_button.h"
#include "../../interfaces/settings.h"

const auto settings = settings::get_instance();

void lights_button::on_click()
{
    switch (settings->light_color)
    {
    case day:
        settings->light_color = night;
        break;
    case night:
        settings->light_color = red;
        break;
    case red:
        settings->light_color = green;
        break;
    case green:
        settings->light_color = blue;
        break;
    case blue:
        settings->light_color = day;
        break;
    }
}

GLuint lights_button::get_texture_id() const
{
    switch (settings::get_instance()->light_color)
    {
    case day: return day_texture_.get_texture_id();
    case night: return night_texture_.get_texture_id();
    case red: return red_texture_.get_texture_id();
    case green: return green_texture_.get_texture_id();
    case blue: return blue_texture_.get_texture_id();
    }
    return 0;
}
