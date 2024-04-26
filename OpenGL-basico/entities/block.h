#pragma once
#include "../geometry/vector3.h"
#include "../geometry/cube.h"
#include "../textures/texture_loader.h"

class block
{
protected:
    float size_ = 1.0f; // tamaño del bloque
    bool active_ = true;
    const vector3 posicion_;
    bool destructible_ = true;
    
public:
    block(const vector3& pos): posicion_(pos) {};
    virtual const texture get_texture() = 0;
    const vector3 get_posicion();
    const cube get_block();
    bool is_active();
    float get_size();
};