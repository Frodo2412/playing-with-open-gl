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
    
    glBindTexture(GL_TEXTURE_2D, entity.get_texture().get_texture_id());
    glBegin(GL_TRIANGLES);

    for (auto& vertex : entity.get_vertices())
    {
        glTexCoord2f(vertex.tex_coords.get_x(), vertex.tex_coords.get_y());
        draw(vertex.position + entity.get_position());
    }

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
    
}

void renderer::draw(const cube& block, const texture& texture)
{
    const auto faces = block.get_faces();

    
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
    
}

void renderer::draw(const square& square, const texture& texture)
{
    
    glBindTexture(GL_TEXTURE_2D, texture.get_texture_id());
    glBegin(GL_QUADS);
    
    glTexCoord2f(0.0f, 1.0f); 
    glVertex3f(square.get_a().get_x(), square.get_a().get_y(), square.get_a().get_z());

    glTexCoord2f(1.0f, 1.0f); 
    glVertex3f(square.get_b().get_x(), square.get_b().get_y(), square.get_b().get_z());

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(square.get_c().get_x(), square.get_c().get_y(), square.get_c().get_z());

    glTexCoord2f(0.0f, 0.0f); 
    glVertex3f(square.get_d().get_x(), square.get_d().get_y(), square.get_d().get_z());
    
    glEnd();
    
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

void renderer::draw(const settings* settings, vector3 bomber_man_pos, const texture& ajustes_texture, const texture& enabled_texture, const texture& disabled_texture)
{
    glEnable(GL_LIGHTING);//ILUMINAR LAS SETTINGS
    glEnable(GL_LIGHT2);
    glLightfv(GL_LIGHT2, GL_POSITION, new float[4]{-0.8f, -0.9f, 0.0f,1.f});
    glLightfv(GL_LIGHT2, GL_DIFFUSE, new float[4]{1.f, 1.f, 1.f, 1.f});
    glLightfv(GL_LIGHT2, GL_AMBIENT, new float[4]{1.f, 1.f, 1.f, 0.0f});
    glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.0f);
    glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.0f);
    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.0f);
    int winHeight = settings->get_instance()->get_winHeigth();
    int winWidth = settings->get_instance()->get_winWidth();

    glBindTexture(GL_TEXTURE_2D, ajustes_texture.get_texture_id());
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex3f(-winWidth/2,-winHeight/2,0);
    glTexCoord2f(1,0);
    glVertex3f(winWidth/2,-winHeight/2,0);
    glTexCoord2f(1,1);
    glVertex3f(winWidth/2,winHeight/2,0);
    glTexCoord2f(0,1);
    glVertex3f(-winWidth/2,winHeight/2,0);
    glEnd();
    
    int enabled_coord_x = winWidth/2 - winWidth*0.28125;
    int enabled_coord_y = winHeight/2 - winHeight*0.322917 + (winHeight-480)*0.05;

    if (settings->get_instance()->get_wireframe_enabled())//VELOCIDAD!!!!!!!!!!
        glBindTexture(GL_TEXTURE_2D, enabled_texture.get_texture_id());
    else
        glBindTexture(GL_TEXTURE_2D, disabled_texture.get_texture_id());
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex3f(enabled_coord_x,enabled_coord_y,1);
    glTexCoord2f(1,0);
    glVertex3f(enabled_coord_x + 50,enabled_coord_y,1);
    glTexCoord2f(1,1);
    glVertex3f(enabled_coord_x + 50,enabled_coord_y + 50,1);
    glTexCoord2f(0,1);
    glVertex3f(enabled_coord_x,enabled_coord_y + 50,1);
    glEnd();
    
    enabled_coord_y = enabled_coord_y - winHeight*0.15;
    settings->get_instance()->set_enabled_screen_coords(0, vector2 (enabled_coord_x + winWidth/2, enabled_coord_y - winHeight/2));

    if (settings->get_instance()->get_wireframe_enabled())
        glBindTexture(GL_TEXTURE_2D, enabled_texture.get_texture_id());
    else
        glBindTexture(GL_TEXTURE_2D, disabled_texture.get_texture_id());
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex3f(enabled_coord_x,enabled_coord_y,1);
    glTexCoord2f(1,0);
    glVertex3f(enabled_coord_x + 50,enabled_coord_y,1);
    glTexCoord2f(1,1);
    glVertex3f(enabled_coord_x + 50,enabled_coord_y + 50,1);
    glTexCoord2f(0,1);
    glVertex3f(enabled_coord_x,enabled_coord_y + 50,1);
    glEnd();
    
    enabled_coord_y = enabled_coord_y - winHeight*0.15;
    settings->get_instance()->set_enabled_screen_coords(1,  vector2 (enabled_coord_x + winWidth/2, enabled_coord_y - winHeight/2));

    if (settings->get_instance()->get_textures_enabled())
        glBindTexture(GL_TEXTURE_2D, enabled_texture.get_texture_id());
    else
        glBindTexture(GL_TEXTURE_2D, disabled_texture.get_texture_id());
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex3f(enabled_coord_x,enabled_coord_y,1);
    glTexCoord2f(1,0);
    glVertex3f(enabled_coord_x + 50,enabled_coord_y,1);
    glTexCoord2f(1,1);
    glVertex3f(enabled_coord_x + 50,enabled_coord_y + 50,1);
    glTexCoord2f(0,1);
    glVertex3f(enabled_coord_x,enabled_coord_y + 50,1);
    glEnd();
    
    enabled_coord_y = enabled_coord_y - winHeight*0.15;
    settings->get_instance()->set_enabled_screen_coords(2, vector2 (enabled_coord_x + winWidth/2, enabled_coord_y - winHeight/2));

    if (settings->get_instance()->get_facetado_enabled())
        glBindTexture(GL_TEXTURE_2D, enabled_texture.get_texture_id());
    else
        glBindTexture(GL_TEXTURE_2D, disabled_texture.get_texture_id());
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex3f(enabled_coord_x,enabled_coord_y,1);
    glTexCoord2f(1,0);
    glVertex3f(enabled_coord_x + 50,enabled_coord_y,1);
    glTexCoord2f(1,1);
    glVertex3f(enabled_coord_x + 50,enabled_coord_y + 50,1);
    glTexCoord2f(0,1);
    glVertex3f(enabled_coord_x,enabled_coord_y + 50,1);
    glEnd();
    
    enabled_coord_y = enabled_coord_y - winHeight*0.15;

    if (settings->get_instance()->get_wireframe_enabled())//LUCES!!!!!!!!!!!
        glBindTexture(GL_TEXTURE_2D, enabled_texture.get_texture_id());
    else
        glBindTexture(GL_TEXTURE_2D, disabled_texture.get_texture_id());
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex3f(enabled_coord_x,enabled_coord_y,1);
    glTexCoord2f(1,0);
    glVertex3f(enabled_coord_x + 50,enabled_coord_y,1);
    glTexCoord2f(1,1);
    glVertex3f(enabled_coord_x + 50,enabled_coord_y + 50,1);
    glTexCoord2f(0,1);
    glVertex3f(enabled_coord_x,enabled_coord_y + 50,1);
    glEnd();
    
    glDisable(GL_LIGHT2);
}
