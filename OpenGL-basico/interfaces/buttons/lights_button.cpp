#include "lights_button.h"
#include "../../utils/settings.h"

GLuint lights_button::get_texture_id() const
{
    switch (settings::get_instance()->get_light_color())
    {
    case day: return day_texture_.get_texture_id();
    case night: return night_texture_.get_texture_id();
    case red: return red_texture_.get_texture_id();
    case green: return green_texture_.get_texture_id();
    case blue: return blue_texture_.get_texture_id();
    }
    return 0;
}
