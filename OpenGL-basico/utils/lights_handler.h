#pragma once
#include "../geometry/vector3.h"
#include "../scene/scene.h"
#include  "../../interfaces/settings.h"

class lights_handler
{
    static lights_handler* instance_;
    lights_handler();

public:
    static lights_handler* get_instance();
    void set_light(camera_mode mode, light_colors light_color, vector3 pos);
};
