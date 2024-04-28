#pragma once
#include "entity.h"
#include "../textures/texture_manager.h"

class enemy final : public entity
{
public:
    explicit enemy(): entity("../assets/models/spider.obj", texture_manager::enemy_texture(), 1)
    {
    }
};
