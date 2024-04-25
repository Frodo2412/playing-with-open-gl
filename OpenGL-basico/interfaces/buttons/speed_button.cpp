#include "speed_button.h"

GLuint speed_button::get_texture_id() const
{
    switch (settings::get_instance()->get_game_velocity())
    {
    case slow: return slow_button_texture_.get_texture_id();
    case normal: return normal_button_texture_.get_texture_id();
    case fast: return fast_button_texture_.get_texture_id();
    }
    return 0;
}
