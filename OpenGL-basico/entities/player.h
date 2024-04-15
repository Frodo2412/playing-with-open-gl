#pragma once
#include "entity.h"

class player : public entity
{
public:
    explicit player(): entity("../../assets/source/bomberman.fbx")
    {
    }
};
