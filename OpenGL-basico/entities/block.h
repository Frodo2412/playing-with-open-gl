#pragma once
#include "../geometry/vector3.h"
#include "../geometry/cube.h"
#include "../textures/texture_loader.h"

class block
{
    vector3 position_;
    cube* cube_;
    texture texture_;

protected:
    explicit block(const vector3& pos, float size, texture texture): position_(pos), cube_(new cube(size, pos)), texture_(texture) {};
    
public:
    const texture get_texture();
    const vector3 get_posicion();
    cube* get_block();

    virtual bool is_destroyable() = 0;
    virtual bool is_active() = 0;
    virtual void destroy() = 0;

    static texture metal_texture;
    static texture brick_texture;
};

