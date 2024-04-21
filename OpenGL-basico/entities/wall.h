#pragma once
#include "../geometry/vector3.h"
#include "../textures/texture_loader.h"

class wall
{
    texture texture_;
    float size_ = 1.0f; // tamaño de la pared
    bool active_ = true;
    const vector3 posicion_;
    bool destructible_ = false;
    
public:
    wall(const vector3& pos) : posicion_(pos), texture_(texture_loader::load_texture("../assets/textures/wall_1.jpg")) {}

    const vector3 get_posicion();
    bool is_state();
    float get_size();
    void draw_wall();
};