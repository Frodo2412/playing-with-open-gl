#include "entity.h"

std::vector<vertex> entity::get_vertices() const
{
    return vertices_;
}

texture entity::get_texture() const
{
    return texture_;
}
