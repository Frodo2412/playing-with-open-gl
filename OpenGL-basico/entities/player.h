#pragma once
#include "entity.h"

class player : public entity
{
public:
    explicit player(): entity("../assets/models/Doodler.obj", "../assets/textures/Doodler.png")
    {
    }

};
