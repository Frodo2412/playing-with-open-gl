#pragma once
#include "entity.h"

class enemy final : public entity
{
public:
    explicit enemy(): entity("../assets/models/spider.obj", "../assets/textures/spider.jpg", 1)
    {
    }
};
