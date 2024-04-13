#pragma once
#include <SDL_opengl.h>

class texture_loader
{
public:
    static GLuint load_texture(const char* file_path);
};
