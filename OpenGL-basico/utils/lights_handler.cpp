﻿#include "lights_handler.h"
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

    if (mode == camera_mode::top_down)
    {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_POSITION, new float[4]{0, 0, 0, 1.f});
        glLightfv(GL_LIGHT0, GL_DIFFUSE, new float[4]{color.get_x(), color.get_y(), color.get_z(), 1.f});
        glLightfv(GL_LIGHT0, GL_AMBIENT, new float[4]{color.get_x(), color.get_y(), color.get_z(), 0.0});
        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.0f);
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0f);
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0000000001f);
    } else
    {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_POSITION, new float[4]{position.get_x(), 0, position.get_z(), 1.f});
        glLightfv(GL_LIGHT0, GL_DIFFUSE, new float[4]{color.get_x(), color.get_y(), color.get_z(), 1.f});
        glLightfv(GL_LIGHT0, GL_AMBIENT, new float[4]{color.get_x(), color.get_y(), color.get_z(), 0.0f});
        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.00000000001f);
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0f);
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0f);
    }
}

void lights_handler::disable_light()

{
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
}
