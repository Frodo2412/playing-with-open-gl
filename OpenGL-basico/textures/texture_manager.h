#pragma once
#include "texture.h"
#include "texture_loader.h"

class texture_manager
{
    static texture_manager* instance_;
    texture player_texture_, enemy_texture_, brick_block_texture_, metal_block_texture_, bomb_texture_, grass_texture_,
            skybox_texture_bk_, skybox_texture_dn_, skybox_texture_ft_, skybox_texture_lf_, skybox_texture_rt_,
            skybox_texture_up_, fire_texture_;

    explicit texture_manager(): player_texture_(texture_loader::load_texture("../assets/textures/bomberman.png")),
                                enemy_texture_(texture_loader::load_texture("../assets/textures/spider.jpg")),
                                brick_block_texture_(texture_loader::load_texture("../assets/textures/bricks_1.jpg")),
                                metal_block_texture_(texture_loader::load_texture("../assets/textures/metal_1.jpg")),
                                bomb_texture_(texture_loader::load_texture("../assets/textures/Bomb.png")),
                                grass_texture_(texture_loader::load_texture("../assets/textures/grass_1.jpg")),
                                skybox_texture_bk_(texture_loader::load_texture("../assets/textures/sh_bk.png")),
                                skybox_texture_dn_(texture_loader::load_texture("../assets/textures/sh_dn.png")),
                                skybox_texture_ft_(texture_loader::load_texture("../assets/textures/sh_ft.png")),
                                skybox_texture_lf_(texture_loader::load_texture("../assets/textures/sh_lf.png")),
                                skybox_texture_rt_(texture_loader::load_texture("../assets/textures/sh_rt.png")),
                                skybox_texture_up_(texture_loader::load_texture("../assets/textures/sh_up.png")),
    fire_texture_(texture_loader::load_texture("../assets/texrures"))
    {
    }

public:
    static void init();

    static texture player_texture();
    static texture enemy_texture();

    static texture brick_block_texture();
    static texture metal_block_texture();

    static texture bomb_texture();
    static texture grass_texture();
    static texture skybox_texture_bk();
    static texture skybox_texture_dn();
    static texture skybox_texture_ft();
    static texture skybox_texture_lf();
    static texture skybox_texture_rt();
    static texture skybox_texture_up();
};
