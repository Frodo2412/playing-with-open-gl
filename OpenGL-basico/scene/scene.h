#pragma once
#include <memory>
#include "../entities/bomb.h"
#include  "../entities/block.h"
#include "../entities/enemy.h"
#include "../entities/metal_block.h"
#include "../scene/camera.h"
#include "../entities/player.h"
#include "../entities/wall_block.h"
#include "../geometry/grid.h"
#include "../utils/particles_handler.h"

enum camera_mode
{
    first,
    top_down,
    perspective
};


class scene final
{
    camera_mode camera_mode_ = first;

    grid floor_;
    static cube skybox_;

    std::unique_ptr<player> player_;
    std::vector<std::unique_ptr<enemy>> enemies_;
    std::vector<std::unique_ptr<block>> blocks_;

    camera* camera_;
    std::vector<std::unique_ptr<bomb>> bombs_;

    void update_camera() const;
    void set_off_bomb(bomb* bomb) const;

    void set_up_wall(int grid_height, int grid_width);
    
public:
    explicit scene(int grid_width, int grid_height);

    void toggle_camera();
    void rotate_camera(float x, float y) const;
    void update_scene(float elapsed_time);
    void move_player(const vector3& displacement) const;
    camera_mode get_camera_mode() const;
    camera* get_camera() const;
    void render_scene(float seconds) const;

    void drop_bomb();
    grid get_floor() const;

    static scene level1();
};
