#pragma once
#include "texture.h"
#include "texture_loader.h"

class texture_manager
{
    static texture_manager* instance_;
    texture player_texture_, enemy_texture_, brick_block_texture_, metal_block_texture_;

    explicit texture_manager(): player_texture_(texture_loader::load_texture("../assets/textures/Doodler.png")),
                                enemy_texture_(texture_loader::load_texture("../assets/textures/spider.jpg")),
                                brick_block_texture_(texture_loader::load_texture("../assets/textures/bricks_1.jpg")),
                                metal_block_texture_(texture_loader::load_texture("../assets/textures/metal_1.jpg"))
    {
    }

public:
    static void init();

    static texture player_texture();
    static texture enemy_texture();

    static texture brick_block_texture();
    static texture metal_block_texture();
};
