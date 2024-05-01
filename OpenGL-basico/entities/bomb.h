#pragma once
#include <memory>
#include "entity.h"
#include "block.h"

class bomb : public entity
{
private:
    int rango_horizontal_;
    int rango_vertical_;
public:
    explicit bomb(): entity("../assets/models/Bomb.obj", "../assets/textures/Diffuse.jpg", 0), rango_horizontal_(3), rango_vertical_(3)
    {
    }
    void explotar(std::vector<block*> bloques);
};