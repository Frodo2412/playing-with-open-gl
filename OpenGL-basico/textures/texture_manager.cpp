#include "texture_manager.h"


texture_manager* texture_manager::instance_ = nullptr;

void texture_manager::init()
{
    instance_ = new texture_manager();
}

texture texture_manager::player_texture()
{
    return instance_->player_texture_;
}

texture texture_manager::enemy_texture()
{
    return instance_->enemy_texture_;
}

texture texture_manager::brick_block_texture()
{
    return instance_->brick_block_texture_;
}

texture texture_manager::metal_block_texture()
{
    return instance_->metal_block_texture_;
}

texture texture_manager::wall_block_texture()
{
    return instance_->wall_block_texture_;
}

texture texture_manager::bomb_texture()
{
    return instance_->bomb_texture_;
}

texture texture_manager::grass_texture()
{
    return instance_->grass_texture_;
}

texture texture_manager::skybox_texture_bk()
{
    return instance_->skybox_texture_bk_;
}

texture texture_manager::skybox_texture_dn()
{
    return instance_->skybox_texture_dn_;
}

texture texture_manager::skybox_texture_ft()
{
    return instance_->skybox_texture_ft_;
}

texture texture_manager::skybox_texture_lf()
{
    return instance_->skybox_texture_lf_;
}

texture texture_manager::skybox_texture_rt()
{
    return instance_->skybox_texture_rt_;
}

texture texture_manager::skybox_texture_up()
{
    return instance_->skybox_texture_up_;
}