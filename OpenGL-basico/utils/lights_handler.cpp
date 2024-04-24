#include "lights_handler.h"
#include "SDL.h"
#include "SDL_opengl.h"
#include <GL/glu.h>

lights_handler* lights_handler::instance_ = nullptr;

lights_handler::lights_handler()
{
}

lights_handler* lights_handler::get_instance()
{
    if (instance_ == nullptr)
    {
        instance_ = new lights_handler();
    }
    return instance_;
}

void lights_handler::set_light(camera_mode mode, light_colors light_color, vector3 position)
{
    vector3 color = vector3(1.f, 1.f, 1.f);

    switch (light_color)
    {
    case light_colors::day:
        color = vector3(1.f, 1.f, 1.f);
        break;
    case light_colors::night:
        color = vector3(0.f, 1.f, 1.f);
        break;
    case light_colors::red:
        color = vector3(1.f, 0.f, 0.f);
        break;
    case light_colors::green:
        color = vector3(0.f, 1.f, 0.f);
        break;
    case light_colors::blue:
        color = vector3(0.f, 0.f, 1.f);
        break;
    }
    
    switch (mode)
    {
    case camera_mode::first:
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
    case camera_mode::top_down:
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
    case camera_mode::perspective:
        //ILUMINACION PERSONAJE
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_POSITION, new float[4]{position.get_x(), 0, position.get_z(), 1.f});
        glLightfv(GL_LIGHT0, GL_DIFFUSE, new float[4]{color.get_x(), color.get_y(), color.get_z(), 1.f});
        glLightfv(GL_LIGHT0, GL_AMBIENT, new float[4]{color.get_x(), color.get_y(), color.get_z(), 0.0f});
        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.0f);
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0f);
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.075f);
        break;
    }
}
