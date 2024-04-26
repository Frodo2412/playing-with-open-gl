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

enum game_velocity
{
    slow,
    normal,
    fast
};

struct settings
{
private:
    static settings* instance_;

public:
    game_velocity game_velocity = normal;
    bool wireframe_enabled = false;
    bool textures_enabled = true;
    bool facetado_enabled = false;
    light_colors light_color = day;
    int window_width = 640;
    int window_height = 480;

    static settings* get_instance();
};
