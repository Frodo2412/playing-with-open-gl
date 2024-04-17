#pragma once
#include "../geometry/vector.h"

enum CameraMode
{
    first,
    original,
    perspective
};

class lights_handler
{
private:
    vector position_;
    CameraMode mode_;
    static lights_handler* instance_;
    lights_handler();
public:
    static lights_handler* get_instance();
    void set_ligth(CameraMode mode, vector pos);
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