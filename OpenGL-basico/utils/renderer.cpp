#include "renderer.h"

#include <SDL_opengl.h>

#include "../textures/texture.h"

void renderer::draw(const triangle& triangle)
{
    glBegin(GL_TRIANGLES);
    draw(triangle.get_a());
    draw(triangle.get_b());
    draw(triangle.get_c());
    glEnd();
}

void renderer::draw(const grid& grid, const texture& texture)
{
    const auto d = grid.get_cell_size() / 2;

    const auto rows = grid.get_rows();
    const auto columns = grid.get_columns();
    const auto size = grid.get_cell_size();

    const auto left = -static_cast<float>(columns) * d;
    const auto top = -static_cast<float>(rows) * d;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture.get_texture_id());
    for (int row = 0; row < rows; ++row)
    {
        glBegin(GL_QUAD_STRIP);
        for (int column = 0; column <= columns; ++column)
        {
            if (column % 2 == row % 2) glColor3f(0.5f, 0.5f, 0.5f); // Set color to medium gray
            else glColor3f(1.0f, 1.0f, 1.0f); // Reset color to white

            glTexCoord2f(0.0, 0.0);
            glVertex3f(left + static_cast<float>(column) * size,
                       -1, top + static_cast<float>(row) * size);
            glTexCoord2f(0.0, 1.0);
            glVertex3f(left + static_cast<float>(column) * size,
                       -1, top + size * (static_cast<float>(row) + 1));
            glTexCoord2f(1.0, 0.0);
            glVertex3f(left + (static_cast<float>(column) + 1) * size,
                       -1, top + size * static_cast<float>(row));
            glTexCoord2f(1.0, 1.0);
            glVertex3f(left + (static_cast<float>(column) + 1) * size,
                       -1, top + size * (static_cast<float>(row) + 1));
        }
        glEnd();
    }
    glDisable(GL_TEXTURE_2D);
}

void renderer::draw(const cube& block, const texture& texture)
{
    const auto faces = block.get_faces();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture.get_texture_id());
    glBegin(GL_QUADS);

    for (auto& face : faces)
    {
        glTexCoord2f(0.0, 0.0);
        draw(face.get_a());
        glTexCoord2f(0.0, 1.0);
        draw(face.get_b());
        glTexCoord2f(1.0, 1.0);
        draw(face.get_c());
        glTexCoord2f(1.0, 0.0);
        draw(face.get_d());
    }

    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void renderer::draw(const square& square, const texture& texture)
{
}

void renderer::draw(const vector& v)
{
    glVertex3f(v.get_x(), v.get_y(), v.get_z());
}
