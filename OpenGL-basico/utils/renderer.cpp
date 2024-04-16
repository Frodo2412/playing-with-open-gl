#include "renderer.h"

#include <iostream>
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

void renderer::draw(const entity& entity)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, entity.get_texture().get_texture_id());
    glBegin(GL_TRIANGLES);

    for (auto& vertex : entity.get_vertices())
    {
        glTexCoord2f(vertex.tex_coords.get_x(), vertex.tex_coords.get_y());
        draw(vertex.position);
    }

    glEnd();
    glDisable(GL_TEXTURE_2D);
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
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture.get_texture_id());
    glBegin(GL_QUADS);
    
    glTexCoord2f(0.0f, 0.0f); 
    glVertex3f(square.get_a().get_x(), square.get_a().get_y(), square.get_a().get_z());
    
    glTexCoord2f(1.0f, 0.0f);  
    glVertex3f(square.get_b().get_x(), square.get_b().get_y(), square.get_b().get_z());

    glTexCoord2f(1.0f, 1.0f); 
    glVertex3f(square.get_c().get_x(), square.get_c().get_y(), square.get_c().get_z());
    
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(square.get_d().get_x(), square.get_d().get_y(), square.get_d().get_z());
    
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void renderer::draw(const vertex& v)
{
    glTexCoord2f(v.tex_coords.get_x(), v.tex_coords.get_y());
    glVertex3f(v.position.get_x(), v.position.get_y(), v.position.get_z());
    glNormal3f(v.normal.get_x(), v.normal.get_y(), v.normal.get_z());
}

void renderer::draw(const vector3& v)
{
    glVertex3f(v.get_x(), v.get_y(), v.get_z());
}
