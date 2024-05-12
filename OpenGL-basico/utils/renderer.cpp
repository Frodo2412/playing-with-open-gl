#include "renderer.h"

#include <iostream>
#include <SDL_opengl.h>

#include "clock.h"
#include "lights_handler.h"
#include "particles_handler.h"
#include "../interfaces/gamehud.h"
#include "../interfaces/settings.h"
#include "../interfaces/settings_screen.h"
#include "../textures/texture.h"

void renderer::draw(const triangle& triangle)
{
    glBegin(GL_TRIANGLES);
    draw(triangle.get_a());
    draw(triangle.get_b());
    draw(triangle.get_c());
    glEnd();
}

void renderer::draw(entity& entity)
{
    const std::vector<vertex> vertices = entity.get_vertices();

    // Create separate arrays for positions, normals, and texture coordinates
    std::vector<float> positions(3 * vertices.size()); // x, y, z for each vertex
    std::vector<float> normals(3 * vertices.size());
    std::vector<float> tex_coords(2 * vertices.size()); // u, v for each vertex

    // Use the smallest scale factor to maintain

    for (size_t i = 0, j = 0; i < vertices.size(); ++i, j += 3)
    {
        positions[j] = vertices[i].position.get_x();
        positions[j + 1] = vertices[i].position.get_y();
        positions[j + 2] = vertices[i].position.get_z();

        normals[j] = vertices[i].normal.get_x();
        normals[j + 1] = vertices[i].normal.get_y();
        normals[j + 2] = vertices[i].normal.get_z();
    }

    for (size_t i = 0, j = 0; i < vertices.size(); ++i, j += 2)
    {
        tex_coords[j] = vertices[i].tex_coords.get_x();
        tex_coords[j + 1] = vertices[i].tex_coords.get_y();
    }

    // Enable the vertex array feature and other features
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    // Specify the format and the address of the arrays
    glVertexPointer(3, GL_FLOAT, 0, positions.data());
    glNormalPointer(GL_FLOAT, 0, normals.data());
    glTexCoordPointer(2, GL_FLOAT, 0, tex_coords.data());
    // Apply the transformations
    glPushMatrix();
    const auto position = entity.get_position();
    //LAS CONSTANSTES ES PARA CENTRAR EL PERSONAJE
    if (entity.is_player_)
    {
        switch (entity.get_new_rotation())
        {
        case up:
            glTranslatef(position.get_x() + 0.6, position.get_y(), position.get_z() + 0.5);
            break;
        case down:
            glTranslatef(position.get_x() - 0.6, position.get_y(), position.get_z() - 0.5);
            break;
        case right:
            glTranslatef(position.get_x() - 0.5, position.get_y(), position.get_z() + 0.6);
            break;
        case left:
            glTranslatef(position.get_x() + 0.5, position.get_y(), position.get_z() - 0.6);
            break;
        }
    }
    else
    {
        glTranslatef(position.get_x(), position.get_y(), position.get_z());
    }


    const auto scale_factor = entity.get_scale_factor();
    glScalef(scale_factor, scale_factor, scale_factor);
    // Bind the texture
    glBindTexture(GL_TEXTURE_2D, entity.get_texture().get_texture_id());
    // Draw the model
    glPushMatrix();
    switch (entity.get_new_rotation())
    {
    case up:
        glRotatef(90, 0, 1, 0);
        break;
    case down:
        glRotatef(-90, 0, 1, 0);
        break;
    case right:
        glRotatef(0, 0, 1, 0);
        break;
    case left:
        glRotatef(180, 0, 1, 0);
        break;
    }

    // Draw the model
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glPopMatrix();
    // Restore the original matrix
    glPopMatrix();

    // Disable the vertex array feature and other features
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    //draw_bounding_box(entity.get_bounding_box().min, entity.get_bounding_box().max);
}

void renderer::draw(const grid& grid, const texture& texture)
{
    const auto rows = grid.get_rows();
    const auto columns = grid.get_columns();
    const auto size = grid.get_cell_size();

    const auto left = grid.get_left();
    const auto top = grid.get_top();


    glBindTexture(GL_TEXTURE_2D, texture.get_texture_id());
    for (int row = 0; row < rows; ++row)
    {
        glBegin(GL_QUAD_STRIP);
        for (int column = 0; column < columns; ++column)
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

void draw_button(const button* button)
{
    glBindTexture(GL_TEXTURE_2D, button->get_texture_id());
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(button->get_top_left_x(), button->get_top_left_y(), 1);
    glTexCoord2f(1, 0);
    glVertex3f(button->get_bottom_right_x(), button->get_top_left_y(), 1);
    glTexCoord2f(1, 1);
    glVertex3f(button->get_bottom_right_x(), button->get_bottom_right_y(), 1);
    glTexCoord2f(0, 1);
    glVertex3f(button->get_top_left_x(), button->get_bottom_right_y(), 1);
    glEnd();
}

void renderer::draw(settings_screen* settings_screen)
{
    const auto settings = ::settings::get_instance();

    const int window_height = settings->window_height;
    const int window_width = settings->window_width;

    glMatrixMode(GL_PROJECTION);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-window_width / 2, window_width / 2, -window_height / 2, window_height / 2, -1.0, 1.0);

    // Draw the background image
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, settings_screen->get_background_texture_id());
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-window_width / 2, -window_height / 2, 0);
    glTexCoord2f(1, 0);
    glVertex3f(window_width / 2, -window_height / 2, 0);
    glTexCoord2f(1, 1);
    glVertex3f(window_width / 2, window_height / 2, 0);
    glTexCoord2f(0, 1);
    glVertex3f(-window_width / 2, window_height / 2, 0);
    glEnd();

    // Draw the buttons
    for (const auto button : settings_screen->get_buttons()) draw_button(button);

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void renderer::draw_gamehud()
{
    glDisable(GL_DEPTH_TEST);
    // Configurar la proyeccion ortogonal
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // Especifico la proyeccion: ortogonal.
    // Configurar la matriz de modelo-vista
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 1.0f);
    const Uint32 time = clock::get_total_time();
    gamehud::draw_time(time);

    // Restaurar la matriz de modelo-vista
    glPopMatrix();
    // Restaurar la matriz de proyeccion
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
}

void renderer::draw_skybox(const cube& skybox)
{
    std::array<texture, 6> textures = {
        texture_manager::skybox_texture_ft(),
        texture_manager::skybox_texture_bk(),
        texture_manager::skybox_texture_up(),
        texture_manager::skybox_texture_dn(),
        texture_manager::skybox_texture_rt(),
        texture_manager::skybox_texture_lf(),
    };


    // Dibuja cada cara del cubo con su respectiva textura
    auto faces = skybox.get_faces();
    for (int i = 0; i < 6; ++i)
    {
        const auto texture = textures[i].get_texture_id();
        glBindTexture(GL_TEXTURE_2D, texture);

        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(faces[i].get_a().get_x(), faces[i].get_a().get_y(), faces[i].get_a().get_z());
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(faces[i].get_b().get_x(), faces[i].get_b().get_y(), faces[i].get_b().get_z());
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(faces[i].get_c().get_x(), faces[i].get_c().get_y(), faces[i].get_c().get_z());
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(faces[i].get_d().get_x(), faces[i].get_d().get_y(), faces[i].get_d().get_z());
        glEnd();
    }
}

void renderer::draw(float seconds, const scene& current_scene, float game_velocity)
{
    if (settings::get_instance()->wireframe_enabled) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if (settings::get_instance()->textures_enabled) glEnable(GL_TEXTURE_2D);
    else glDisable(GL_TEXTURE_2D);
    if (settings::get_instance()->facetado_enabled) glShadeModel(GL_FLAT);
    else glShadeModel(GL_SMOOTH);

    current_scene.render_scene(seconds, game_velocity);
}

void renderer::draw(particle* particle)
{
    glDisable(GL_LIGHTING);
    float r = particle->get_color().get_r();
    float g = particle->get_color().get_g();
    float b = particle->get_color().get_b();
    float alpha = particle->get_color().get_alpha();
    float x = particle->get_position().get_x();
    float y = particle->get_position().get_y();
    float z = particle->get_position().get_z();
    float size = particle->get_size();
    glPointSize(size); //TAMANIO DE LAS PARTICULAS(PUNTOS)
    glBegin(GL_POINTS);
    glColor4f(r, g, b, alpha);
    glVertex3f(x, y, z);
    glEnd();
    glEnable(GL_LIGHTING);
}


void renderer::draw(float seconds, particles_handler* particles_handler, float game_velocity)
{
    particles_handler->get_instance()->update(seconds, game_velocity);
    for (particle* particle : particles_handler->get_instance()->get_particles())
    {
        draw(particle);
    }
}

void renderer::draw(menu* menu)
{
    const auto settings = ::settings::get_instance();

    const int window_height = settings->window_height;
    const int window_width = settings->window_width;

    glMatrixMode(GL_PROJECTION);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-window_width / 2, window_width / 2, -window_height / 2, window_height / 2, -1.0, 1.0);

    // Draw the background image
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, menu->get_background_texture_id());
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-window_width / 2, -window_height / 2, 0);
    glTexCoord2f(1, 0);
    glVertex3f(window_width / 2, -window_height / 2, 0);
    glTexCoord2f(1, 1);
    glVertex3f(window_width / 2, window_height / 2, 0);
    glTexCoord2f(0, 1);
    glVertex3f(-window_width / 2, window_height / 2, 0);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

