#pragma once
#include <SDL_opengl.h>

class texture
{
    GLuint texture_id_;

public:

    explicit texture(const GLuint texture_id): texture_id_(texture_id)
    {
    }

    GLuint get_texture_id() const;
};
