#include "settings.h"
#include <iostream>

settings* settings::instance_ = nullptr;

settings::settings()
{
    slow_mode_ = false;
    wireframe_enabled_ = false;
    textures_enabled_ = true;
    facetado_enabled_ = false;
    light_color_ = light_colors::natural;
}

settings* settings::get_instance()
{
    if (instance_ == nullptr)
        instance_ = new settings();
    return instance_;
}


void settings::set_slow_mode(bool slow_mode)
{
    slow_mode_ = slow_mode;
}

bool settings::get_slow_mode()
{
    return slow_mode_;
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
    if (x >= enabled_screen_coords[0].get_x() && x <= enabled_screen_coords[0].get_x() + 50 && y >= enabled_screen_coords[0].get_y() && y <= enabled_screen_coords[0].get_y() + 50)
    {
        slow_mode_ = !slow_mode_;
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
        std::cout << "entro Facetado" << std::endl;
        facetado_enabled_ = !facetado_enabled_;
    }
}

settings::~settings()
{
}
