#include "settings.h"
#include <iostream>

settings* settings::instance_ = nullptr;

settings::settings()
{
    game_velocity_ = game_velocity::normal;
    wireframe_enabled_ = false;
    textures_enabled_ = true;
    facetado_enabled_ = false;
    light_color_ = light_colors::day;
}

settings* settings::get_instance()
{
    if (instance_ == nullptr)
        instance_ = new settings();
    return instance_;
}


void settings::set_game_velocity(game_velocity game_velocity)
{
    game_velocity_ = game_velocity;
}

game_velocity settings::get_game_velocity()
{
    return game_velocity_;
}

void settings::set_wireframe_enabled(bool wireframe)
{
    wireframe_enabled_ = wireframe;
}

bool settings::get_wireframe_enabled()
{
    return wireframe_enabled_;
}

void settings::set_light_color(light_colors color)
{
    light_color_ = color;
}

light_colors settings::get_light_color()
{
    return light_color_;
}

int settings::get_winHeigth()
{
    return winHeigth;
}

int settings::get_winWidth()
{
    return winWidth;
}

void settings::set_winHeigth(int winHeigth)
{
    this->winHeigth = winHeigth;
}

void settings::set_winWidth(int winWidth)
{
    this->winWidth = winWidth;
}

bool settings::get_textures_enabled()
{
    return textures_enabled_;
}

void settings::set_textures_enabled(bool textures_enabled)
{
    textures_enabled_ = textures_enabled;
}

bool settings::get_facetado_enabled()
{
    return facetado_enabled_;
}

void settings::set_facetado_enabled(bool facetado_enabled)
{
    facetado_enabled_ = facetado_enabled;
}

void settings::set_enabled_screen_coords(int index, vector2 vector)
{
    enabled_screen_coords[index] = vector;
}

void settings::event_handler(int x, int y)
{
    if (x >= enabled_screen_coords[0].get_x() && x <= enabled_screen_coords[0].get_x() + 100 && y >= enabled_screen_coords[0].get_y() && y <= enabled_screen_coords[0].get_y() + 50)
    {
        switch (game_velocity_)
        {
        case game_velocity::slow:
            game_velocity_ = game_velocity::normal;
            break;
        case game_velocity::normal:
            game_velocity_ = game_velocity::fast;
            break;
        case game_velocity::fast:
            game_velocity_ = game_velocity::slow;
            break;
        }
    }
    if (x >= enabled_screen_coords[1].get_x() && x <= enabled_screen_coords[1].get_x() + 50 && y >= enabled_screen_coords[1].get_y() && y <= enabled_screen_coords[1].get_y() + 50)
    {
        wireframe_enabled_ = !wireframe_enabled_;
    }
    if (x >= enabled_screen_coords[2].get_x() && x <= enabled_screen_coords[2].get_x() + 50 && y >= enabled_screen_coords[2].get_y() && y <= enabled_screen_coords[2].get_y() + 50)
    {
        textures_enabled_ = !textures_enabled_;
    }
    if (x >= enabled_screen_coords[3].get_x() && x <= enabled_screen_coords[3].get_x() + 50 && y >= enabled_screen_coords[3].get_y() && y <= enabled_screen_coords[3].get_y() + 50)
    {
        facetado_enabled_ = !facetado_enabled_;
    }
    if (x >= enabled_screen_coords[4].get_x() && x <= enabled_screen_coords[4].get_x() + 100 && y >= enabled_screen_coords[4].get_y() && y <= enabled_screen_coords[4].get_y() + 50)
    {
        switch (light_color_)
        {
        case light_colors::day:
            light_color_ = light_colors::night;
            break;
        case light_colors::night:
            light_color_ = light_colors::red;
            break;
        case light_colors::red:
            light_color_ = light_colors::green;
            break;
        case light_colors::green:
            light_color_ = light_colors::blue;
            break;
        case light_colors::blue:
            light_color_ = light_colors::day;
            break;
        }
    }
}

texture settings::get_ajustes_texture()
{
    return ajustes_texture;
}

texture settings::get_slow_settings_texture()
{
    return slow_settings_texture;
}

texture settings::get_normal_settings_texture()
{
    return normal_settings_texture;
}

texture settings::get_fast_settings_texture()
{
    return fast_settings_texture;
}

texture settings::get_enabled_texture()
{
    return enabled_texture;
}

texture settings::get_disabled_texture()
{
    return disabled_texture;
}

texture settings::get_day_settings_texture()
{
    return day_settings_texture;
}

texture settings::get_night_settings_texture()
{
    return night_settings_texture;
}

texture settings::get_red_settings_texture()
{
    return red_settings_texture;
}

texture settings::get_green_settings_texture()
{
    return green_settings_texture;
}

texture settings::get_blue_settings_texture()
{
    return blue_settings_texture;
}

settings::~settings()
{
}
