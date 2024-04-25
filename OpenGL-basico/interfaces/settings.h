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
    vector2 window_size = vector2(640, 480);

    static settings* get_instance();
};
