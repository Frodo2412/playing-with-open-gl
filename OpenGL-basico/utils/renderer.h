#pragma once

#include "../scene/camera.h"
#include "../entities/entity.h"
#include "../geometry/cube.h"
#include "../geometry/Triangle.h"
#include "../geometry/vector3.h"
#include "../geometry/grid.h"
#include "../textures/texture.h"
#include "./settings.h"

class renderer
{
public:
    static void draw(const grid& grid, const texture& texture);
    static void draw(const cube& block, const texture& texture);
    static void draw(const vertex& v);
    static void draw(const vector3& v);
    static void draw(const triangle& triangle);
    static void draw(const entity& entity);
    static void draw(const square&, const texture& texture);
    static void draw(const settings* settings, vector3 bomber_man_pos, const texture& ajustes_texture,
                            const texture& enabled_texture, const texture& disabled_texture, const texture& day_settings_texture,
                            const texture& night_settings_texture, const texture& red_settings_texture,
                            const texture& green_settings_texture, const texture& blue_settings_texture);
};

