
#pragma once
#include "../geometry/vector2.h"

enum light_colors
{
    day,
    night,
    red,
    green,
    blue
};

class settings
{
private:
    bool slow_mode_ = false;
    bool wireframe_enabled_ = false;
    bool textures_enabled_ = true;
    bool facetado_enabled_ = false;
    light_colors light_color_;
    static settings* instance_;
    int winHeigth;
    int winWidth;
    vector2 enabled_screen_coords[5];
    settings();
public:
    static settings* get_instance();
    void set_slow_mode(bool slow_mode);
    bool get_slow_mode();
    void set_wireframe_enabled(bool wireframe);
    bool get_wireframe_enabled();
    void set_light_color(light_colors color);
    light_colors get_light_color();
    int get_winHeigth();
    int get_winWidth();
    void set_winHeigth(int winHeigth);
    void set_winWidth(int winWidth);
    bool get_textures_enabled();
    void set_textures_enabled(bool textures_enabled);
    bool get_facetado_enabled();
    void set_facetado_enabled(bool facetado_enabled);
    void event_handler(int x, int y);
    void set_enabled_screen_coords(int index, vector2 vector);
    ~settings();
};