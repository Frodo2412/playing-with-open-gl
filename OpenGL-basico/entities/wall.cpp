#include "wall.h"
#include "../utils/renderer.h"
#include "../geometry/cube.h"

void wall::draw_wall()
{
    if(this->active_){ // si el bloque está activo, lo dibujo.
        const auto pared = cube(this->size_, this->posicion_);
        renderer::draw(pared, this->texture_);
    }
}

const vector3 wall::get_posicion()
{
    return posicion_;
};

bool wall::is_state(){
    return active_;
};

float wall::get_size()
{
    return size_;
};