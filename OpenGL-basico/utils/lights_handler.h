#pragma once
#include "../geometry/vector3.h"
#include "../camera/camera_handler.h"

class lights_handler
{
private:
    vector3 position_;
    camera_mode mode_;
    static lights_handler* instance_;
    lights_handler();
public:
    static lights_handler* get_instance();
    void set_light(camera_mode mode, vector3 pos);
};