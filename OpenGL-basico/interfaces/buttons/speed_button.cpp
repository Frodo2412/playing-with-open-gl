#include "speed_button.h"

const auto settings = settings::get_instance();

void speed_button::on_click()
{
    switch (settings->game_velocity)
    {
    case slow:
        settings->game_velocity = normal;
        break;
    case normal:
        settings->game_velocity = fast;
        break;
    case fast:
        settings->game_velocity = slow;
        break;
    }
}

GLuint speed_button::get_texture_id() const
{
    switch (settings::get_instance()->game_velocity)
    {
    case slow: return slow_button_texture_.get_texture_id();
    case normal: return normal_button_texture_.get_texture_id();
    case fast: return fast_button_texture_.get_texture_id();
    }
    return 0;
}
