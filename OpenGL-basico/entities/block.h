#pragma once
#include "../geometry/vector3.h"
#include "../textures/texture_loader.h"

class block
{
    texture texture_;
    float size_ = 1.0f; // tamaño del bloque
    bool active_ = true;
    const vector3 posicion_;
    bool destructible_ = true;
    
public:
    block(const vector3& pos) : posicion_(pos), texture_(texture_loader::load_texture("../assets/textures/bricks_1.jpg")) {}

    const vector3 get_posicion();
    bool is_state();
    float get_size();
    void draw_block();
    void destruir();
};