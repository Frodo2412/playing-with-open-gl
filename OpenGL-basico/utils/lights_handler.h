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


//COMO USAR LAS CAMARAS
/*
case CameraMode::first:
                //ILUMINACION PERSONAJE
                lights_handler->set_ligth(CameraMode::first, camera.get_direction());

            case CameraMode::original:
                //ILUMINACION GLOBAL
                lights_handler->set_ligth(CameraMode::original, vector(0, -1, 0));

            case CameraMode::perspective:

                    lights_handler->set_ligth(CameraMode::perspective, vector(0, 0, 0));

        }*/