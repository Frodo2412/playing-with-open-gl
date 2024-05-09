#pragma once
#include <memory>
#include "../entities/bomb.h"
#include  "../entities/block.h"
#include  "../entities/metal_block.h"
#include  "../entities/brick_block.h"
#include "../entities/enemy.h"
#include "../scene/camera.h"
#include "../entities/player.h"
#include "../geometry/grid.h"

enum camera_mode
{
    first,
    top_down,
    perspective
};


class scene
{
    camera_mode camera_mode_ = first;

    grid floor_;

    camera* camera_;
    std::vector<std::unique_ptr<bomb>> bombs_;

    void update_camera() const;
    void set_off_bomb(bomb* bomb) const;

protected:
    std::unique_ptr<player> player_;
    std::vector<std::unique_ptr<enemy>> enemies_;
    std::vector<std::unique_ptr<block>> blocks_;

public:
    explicit scene(): floor_(grid(11, 17, 10, vector3(0, 0, 0))), camera_(new camera(0, 0, 0))
    {
        enemies_.emplace_back(std::make_unique<enemy>(enemy()));
        blocks_.push_back(std::make_unique<brick_block>(vector3(0.5, -0.5, 0)));
        blocks_.push_back(std::make_unique<brick_block>(vector3(1.5, -0.5, 0)));
        blocks_.push_back(std::make_unique<metal_block>(vector3(2.5, -0.5, 0)));
        blocks_.push_back(std::make_unique<metal_block>(vector3(1.5, -0.5, 1)));
    }

    explicit scene(const vector3& initial_player_position, std::vector<std::unique_ptr<enemy>> enemies,
                   std::vector<std::unique_ptr<block>> blocks)
        : floor_(grid(10, 10, 1, vector3(0, 1, 0))),
          camera_(
              new camera(
                  initial_player_position.get_x(),
                  initial_player_position.get_y(),
                  initial_player_position.get_z())), player_(std::make_unique<player>()), enemies_(std::move(enemies)),
          blocks_(std::move(blocks))
    {
    }

    void toggle_camera();
    void rotate_camera(float x, float y) const;
    void update_scene(float elapsed_time);
    void move_player(const vector3& displacement) const;
    camera_mode get_camera_mode() const;
    camera* get_camera() const;
    void render_scene() const;


    void drop_bomb();
    grid get_floor() const;
};
