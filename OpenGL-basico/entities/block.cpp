#include "block.h"
#include "../utils/renderer.h"
#include "../geometry/cube.h"

const vector3 block::get_posicion()
{
    return posicion_;
}

const cube block::get_block()
{
    const auto pared = cube(this->size_, this->posicion_);
    return pared;
};

bool block::is_active(){
    return active_;
};

float block::get_size()
{
    return size_;
};
