#include "block.h"
#include "../utils/renderer.h"
#include "../geometry/cube.h"

void block::draw_block()
{
    if(this->active_){ // si el bloque está activo, lo dibujo.
        const auto bloque = cube(this->size_, this->posicion_);
        renderer::draw(bloque, this->texture_);
    }
}

void block::destruir()
{
    this->active_ = false; // la bomba pasa a estar inactiva.
}

const vector3 block::get_posicion()
{
    return posicion_;
};

bool block::is_state(){
    return active_;
};

float block::get_size()
{
    return size_;
};