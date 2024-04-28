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
