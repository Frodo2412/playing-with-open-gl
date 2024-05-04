#pragma once
#include "../geometry/vector3.h"
#include "../scene/scene.h"
#include  "../../interfaces/settings.h"

class lights_handler
{
public:
    static void set_light(camera_mode mode, light_colors light_color, const vector3& position);
    static void disable_light();
};
