#pragma once

#include "camera.h"
#include "../entities/entity.h"
#include "../geometry/cube.h"
#include "../geometry/Triangle.h"
#include "../geometry/vector3.h"
#include "../geometry/grid.h"
#include "../textures/texture.h"

class renderer
{
public:
    static void draw(const grid& grid, const texture& texture);
    static void draw(const cube& block, const texture& texture);
    static void draw(const vertex& v);
    static void draw(const vector3& v);
    static void draw(const triangle& triangle);
    static void draw(const entity& entity);
};
