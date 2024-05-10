#pragma once

#include "../entities/entity.h"
#include "../geometry/cube.h"
#include "../geometry/Triangle.h"
#include "../geometry/vector3.h"
#include "../geometry/grid.h"
#include "../scene/scene.h"
#include "../textures/texture.h"
#include "particles_handler.h"

class settings_screen;

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
    static void draw(settings_screen* settings_screen);
    static void draw_gamehud();
    static void draw_skybox(const cube& skybox);
    static void draw(float seconds, const scene& current_scene);
    static void draw(particle* particle);
    static void draw(float seconds, particles_handler* particles_handler);
};
