#pragma once
#include "entity.h"
#include "block.h"
#include "enemy.h"

class bomb : public entity
{
private:
    float timer_;
    bool exploded_;
    int rango_horizontal_;
    int rango_vertical_;
public:
    explicit bomb(): entity("../assets/models/Bomb.obj", "../assets/textures/Diffuse.jpg", 1), rango_horizontal_(3), rango_vertical_(3), timer_(5), exploded_(false)
    {
    }
    void explotar(std::vector<block*>& bloques, std::vector<enemy>& enemies);
    const bool is_exploded();
    const float get_timer();
    void set_timer(float timer);
};