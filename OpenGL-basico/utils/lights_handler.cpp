#include "lights_handler.h"
#include "SDL.h"
#include "SDL_opengl.h"

void lights_handler::set_light(const camera_mode mode, const light_colors light_color, const vector3& position)
{
    auto color = vector3(1.f, 1.f, 1.f);

    switch (light_color)
    {
    case day:
        color = vector3(1.f, 1.f, 1.f);
        break;
    case night:
        color = vector3(0.f, 1.f, 1.f);
        break;
    case red:
        color = vector3(1.f, 0.f, 0.f);
        break;
    case green:
        color = vector3(0.f, 1.f, 0.f);
        break;
    case blue:
        color = vector3(0.f, 0.f, 1.f);
        break;
    }

    switch (mode)
    {
    case first:
        //ILUMINACION PERSONAJE
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_POSITION, new float[4]{position.get_x(), 0, position.get_z(), 1.f});
        glLightfv(GL_LIGHT0, GL_DIFFUSE, new float[4]{color.get_x(), color.get_y(), color.get_z(), 1.f});
        glLightfv(GL_LIGHT0, GL_AMBIENT, new float[4]{color.get_x(), color.get_y(), color.get_z(), 0.0f});
        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.0f);
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0f);
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.01f);
        break;
    case top_down:
        //ILUMINACION GLOBAL
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_POSITION, new float[4]{0, 0, 0, 1.f});
        glLightfv(GL_LIGHT0, GL_DIFFUSE, new float[4]{color.get_x(), color.get_y(), color.get_z(), 1.f});
        glLightfv(GL_LIGHT0, GL_AMBIENT, new float[4]{color.get_x(), color.get_y(), color.get_z(), 0.f});
        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.0f);
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0f);
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0000000000000001f);
        break;
    case perspective:
        //ILUMINACION PERSONAJE
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_POSITION, new float[4]{position.get_x(), 0, position.get_z(), 1.f});
        glLightfv(GL_LIGHT0, GL_DIFFUSE, new float[4]{color.get_x(), color.get_y(), color.get_z(), 1.f});
        glLightfv(GL_LIGHT0, GL_AMBIENT, new float[4]{color.get_x(), color.get_y(), color.get_z(), 0.0f});
        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.0f);
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0f);
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0000000000000001f);
        break;
    }

    // Assuming other lights and settings are already initialized
    glEnable(GL_LIGHT1); // Enable an additional light

    // Define the color components for the new light
    constexpr GLfloat ambient_light[] = {0.2f, 0.2f, 0.2f, 1.0f}; // Dim white for ambient light
    constexpr GLfloat diffuse_light[] = {1.0f, 1.0f, 1.0f, 1.0f}; // Full white for diffuse light
    constexpr GLfloat specular_light[] = {1.0f, 1.0f, 1.0f, 1.0f}; // Full white for specular light

    // Set up the new light properties
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular_light);

    // Position the new light as a directional light
    constexpr GLfloat light_position[] = {-1.0f, 2.0f, 1.0f, 0.0f}; // Example directional vector
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);
}

void lights_handler::disable_light()
{
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT1);
    glDisable(GL_LIGHTING);
}
