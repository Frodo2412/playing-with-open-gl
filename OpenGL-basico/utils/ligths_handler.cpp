#include "lights_handler.h"
#include "SDL.h"
#include "SDL_opengl.h"
#include <GL/glu.h>

lights_handler* lights_handler::instance_ = nullptr;

lights_handler::lights_handler()
{
    position_ = vector(0, 0, 0);
}

lights_handler* lights_handler::get_instance()
{
    if (instance_ == nullptr)
    {
        instance_ = new lights_handler();
    }
    return instance_;
}

void lights_handler::set_ligth(CameraMode mode, vector pos)
{
    position_ = pos;
    mode_ = mode;
    switch (mode_)
    {
    case CameraMode::first:
        //ILUMINACION PERSONAJE
            glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_POSITION, new float[4]{position_.get_x(), 0, position_.get_z()+10, 1.f});
        glLightfv(GL_LIGHT0, GL_DIFFUSE, new float[4]{1.f, 1.f, 1.f, 1.f});
        glLightfv(GL_LIGHT0, GL_AMBIENT, new float[4]{0.f, 0.f, 0.f, 0.f});
        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.0f);
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0f);
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0055f);
        break;
    case CameraMode::original:
        //ILUMINACION GLOBAL
            glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_POSITION, new float[4]{0.f,-1.f,0.f,0.f});
        glLightfv(GL_LIGHT0, GL_DIFFUSE, new float[4]{1.f, 1.f, 1.f, 1.f});
        glLightfv(GL_LIGHT0, GL_AMBIENT, new float[4]{0.f, 0.f, 0.f, 0.f});
        break;
    case CameraMode::perspective:
        //ILUMINACION PERSONAJE
            glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_POSITION, new float[4]{0, 0, 0, 1.f});
        glLightfv(GL_LIGHT0, GL_DIFFUSE, new float[4]{1.f, 1.f, 1.f, 1.f});
        glLightfv(GL_LIGHT0, GL_AMBIENT, new float[4]{0.f, 0.f, 0.f, 0.f});
        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.0f);
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0f);
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.01f);
        break;
    }
}