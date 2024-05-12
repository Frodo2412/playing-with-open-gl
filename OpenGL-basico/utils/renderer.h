#pragma once

#include "../entities/entity.h"
#include "../geometry/cube.h"
#include "../geometry/Triangle.h"
#include "../geometry/vector3.h"
#include "../geometry/grid.h"
#include "../scene/scene.h"
#include "../textures/texture.h"
#include "particles_handler.h"
#include "../interfaces/menu.h"

class settings_screen;

class renderer
{
public:
    static void draw(const grid& grid, const texture& texture);
    static void draw(const cube& block, const texture& texture);
    static void draw(const vertex& v);
    static void draw(const vector3& v);
    static void draw(const triangle& triangle);
    static void draw(entity& entity);
    static void draw(const square&, const texture& texture);
    static void draw(settings_screen* settings_screen);
    static void draw_gamehud();
    static void draw_skybox(const cube& skybox);
    static void draw(float seconds, const scene& current_scene, float game_velocity);
    static void draw(particle* particle);
    static void draw(float seconds, particles_handler* particles_handler, float game_velocity);
    static void draw(menu* menu);
    static void draw_bounding_box(const vector3& min, const vector3& max)
    {
        GLfloat vertices[] = {
            min.get_x(), min.get_y(), min.get_z(),
            max.get_x(), min.get_y(), min.get_z(),
            max.get_x(), max.get_y(), min.get_z(),
            min.get_x(), max.get_y(), min.get_z(),
            min.get_x(), min.get_y(), max.get_z(),
            max.get_x(), min.get_y(), max.get_z(),
            max.get_x(), max.get_y(), max.get_z(),
            min.get_x(), max.get_y(), max.get_z()
        };

        GLubyte indices[] = {
            0, 1, 1, 2, 2, 3, 3, 0, // Bottom face
            4, 5, 5, 6, 6, 7, 7, 4, // Top face
            0, 4, 1, 5, 2, 6, 3, 7 // Side edges
        };

        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertices);
        glDrawElements(GL_LINES, 24, GL_UNSIGNED_BYTE, indices);
        glDisableClientState(GL_VERTEX_ARRAY);
    }
};
