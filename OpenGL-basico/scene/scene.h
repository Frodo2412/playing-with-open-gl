#pragma once
#include <memory>
#include "../entities/bomb.h"
#include  "../entities/block.h"
#include "../entities/enemy.h"
#include "../entities/metal_block.h"
#include "../scene/camera.h"
#include "../entities/player.h"
#include "../geometry/grid.h"
#include "../utils/particles_handler.h"
#include "../utils/sound.h"

enum camera_mode
{
    first,
    top_down,
    perspective
};

struct coordinate
{
    int height, width;
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

    explicit scene(int number, int grid_width, int grid_height, std::vector<coordinate>& brick_blocks,
                   std::vector<coordinate>& metal_blocks, std::vector<coordinate>& enemies);

public:
    const int level_number;

    void toggle_camera();
    void set_camera(camera_mode);
    void rotate_camera(float x, float y) const;
    void update_scene(float elapsed_time, sound& explosion);
    void move_player(const vector3& displacement) const;
    camera_mode get_camera_mode() const;
    camera* get_camera() const;
    void render_scene(float seconds, float game_velocity) const;

    void drop_bomb();
    grid get_floor() const;

    static scene* level1();
    static scene* level2(camera_mode mode);
    static scene* level3(camera_mode mode);
    static scene* level4(camera_mode mode);
    static scene* level5(camera_mode mode);

    static scene* get_level(int number, camera_mode mode);
};
