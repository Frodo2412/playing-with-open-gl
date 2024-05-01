#pragma once
#include "entity.h"

class enemy final : public entity
{
private:
    bool active_;
public:
    explicit enemy(): entity("../assets/models/spider.obj", "../assets/textures/spider.jpg", 1), active_(true)
    {
    }
    const bool is_active();
    void destroy();
};
