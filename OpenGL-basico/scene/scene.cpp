#include "scene.h"

#include <GL/glu.h>

#include "../entities/bomb.h"
#include "../utils/renderer.h"
#include  "../entities/brick_block.h"
#include  "../entities/metal_block.h"
#include "../interfaces/settings.h"
#include "../utils/lights_handler.h"
#include "../entities/wall_block.h"

cube scene::skybox_ = cube(50.0f, vector3(0, 4, 0));

const auto settings = settings::get_instance();
particles_handler* particles_handler_ = particles_handler::get_instance();

void scene::toggle_camera()
{
    switch (camera_mode_)
    {
    case first:
        camera_mode_ = top_down;
        camera_->set_position(player_->get_position() + vector3(0.5, 10, 0));
        camera_->set_direction(player_->get_position() + vector3(0.5, 0, 0));
        camera_->set_up(vector3(0, 0, -1));
        break;
    case top_down:
        {
            camera_mode_ = perspective;
            camera_->set_position(player_->get_position() + vector3(0.5, 5, 5));
            camera_->set_direction(player_->get_position() + vector3(0.5, 1, 0));
            camera_->set_up(vector3(0, 1, 0));
            break;
        }
    case perspective:
        camera_mode_ = first;
        camera_->set_up(player_->get_up());
        camera_->set_direction(player_->get_direction());
        camera_->set_position(player_->get_position());
        break;
    }
}

void scene::rotate_camera(const float x, const float y) const
{
    switch (camera_mode_)
    {
    case first:
        camera_->rotate(x, y);
        player_->set_direction(camera_->get_direction());
        break;
    case perspective:
        camera_->rotate(-x * 0.3, y * 0.3);
        break;
    case top_down:
        break;
    }
}

void scene::update_camera() const
{
    switch (camera_mode_)
    {
    case first:
        camera_->move(player_.get());
        camera_->set_position(vector3(camera_->get_position().get_x(), -0.2, camera_->get_position().get_z()));
        break;
    case perspective:
        camera_->move(player_->get_speed());
        break;
    case top_down:
        camera_->move(player_->get_speed());
        break;
    }
}

void scene::set_off_bomb(bomb* bomb) const
{
    bomb->explotar();
    bool continuar = true;

    int i_max = bomb::radius;
    int k_min = -bomb::radius;
    int j_max = bomb::radius;
    int l_min = -bomb::radius;

    //ROMPER HORIZONTAL
    for (int i = 0; i <= bomb::radius; i++)
    {
        vector3 pos = bomb->get_position() + vector3(static_cast<float>(i), 0, 0);
        for (const auto& bloque : blocks_)
        {
            brick_block* bloque_destructible = dynamic_cast<brick_block*>(bloque.get());
            if (bloque_destructible != nullptr && bloque_destructible->get_position().get_x() + 0.5 > pos.get_x() &&
                bloque_destructible->get_position().get_x() - 0.5 < pos.get_x() && bloque_destructible->
                get_position().
                get_z() + 0.5 > pos.get_z() && bloque_destructible->get_position().get_z() - 0.5 < pos.get_z())
            {
                bloque_destructible->destroy();
            }
            else if (bloque_destructible == nullptr)
            // si no es un bloque destructible --> es no destructible, para la explosión.
            {
                metal_block* bloque_no_destructible = dynamic_cast<metal_block*>(bloque.get());
                if (bloque_no_destructible != nullptr && bloque_no_destructible->get_position().get_x() + 0.5 > pos.
                    get_x() && bloque_no_destructible->get_position().get_x() - 0.5 < pos.get_x() &&
                    bloque_no_destructible->get_position().get_z() + 0.5 > pos.get_z() && bloque_no_destructible->
                    get_position().get_z() - 0.5 < pos.get_z())
                {
                    i_max = i;
                    continuar = false;
                    break;
                }
            }
        }
        if (!continuar)
            break;
    }
    continuar = true;
    for (int k = -bomb::radius; k < 0; k++)
    {
        vector3 pos = bomb->get_position() + vector3(static_cast<float>(k), 0, 0);
        for (auto& bloque : blocks_)
        {
            auto bloque_destructible = dynamic_cast<brick_block*>(bloque.get());
            if (bloque_destructible != nullptr && bloque_destructible->get_position().get_x() + 0.5 > pos.get_x() &&
                bloque_destructible->get_position().get_x() - 0.5 < pos.get_x() && bloque_destructible->
                get_position().
                get_z() + 0.5 > pos.get_z() && bloque_destructible->get_position().get_z() - 0.5 < pos.get_z())
            {
                bloque_destructible->destroy();
            }
            else if (bloque_destructible == nullptr)
            // si no es un bloque destructible --> es no destructible, para la explosión.
            {
                metal_block* bloque_no_destructible = dynamic_cast<metal_block*>(bloque.get());
                if (bloque_no_destructible != nullptr && bloque_no_destructible->get_position().get_x() + 0.5 > pos.
                    get_x() && bloque_no_destructible->get_position().get_x() - 0.5 < pos.get_x() &&
                    bloque_no_destructible->get_position().get_z() + 0.5 > pos.get_z() && bloque_no_destructible->
                    get_position().get_z() - 0.5 < pos.get_z())
                {
                    k_min = k;
                    continuar = false;
                    break;
                }
            }
        }
        if (!continuar)
            break;
    }
    continuar = true;
    //ROMPER VERTICAL
    for (int j = 0; j <= bomb::radius; j++)
    {
        vector3 pos = bomb->get_position() + vector3(0, 0, static_cast<float>(j));
        for (auto& bloque : blocks_)
        {
            brick_block* bloque_destructible = dynamic_cast<brick_block*>(bloque.get());
            if (bloque_destructible != nullptr && bloque_destructible->get_position().get_x() + 0.5 > pos.get_x() &&
                bloque_destructible->get_position().get_x() - 0.5 < pos.get_x() && bloque_destructible->
                get_position().
                get_z() + 0.5 > pos.get_z() && bloque_destructible->get_position().get_z() - 0.5 < pos.get_z())
            {
                bloque_destructible->destroy();
            }
            else if (bloque_destructible == nullptr)
            // si no es un bloque destructible --> es no destructible, para la explosión.
            {
                metal_block* bloque_no_destructible = dynamic_cast<metal_block*>(bloque.get());
                if (bloque_no_destructible != nullptr && bloque_no_destructible->get_position().get_x() + 0.5 > pos.
                    get_x() && bloque_no_destructible->get_position().get_x() - 0.5 < pos.get_x() &&
                    bloque_no_destructible->get_position().get_z() + 0.5 > pos.get_z() && bloque_no_destructible->
                    get_position().get_z() - 0.5 < pos.get_z())
                {
                    j_max = j;
                    continuar = false;
                    break;
                }
            }
        }
        if (!continuar)
            break;
    }
    continuar = true;
    for (int l = -bomb::radius; l < 0; l++)
    {
        vector3 pos = bomb->get_position() + vector3(0, 0, static_cast<float>(l));
        for (auto& bloque : blocks_)
        {
            brick_block* bloque_destructible = dynamic_cast<brick_block*>(bloque.get());
            if (bloque_destructible != nullptr && bloque_destructible->get_position().get_x() + 0.5 > pos.get_x() &&
                bloque_destructible->get_position().get_x() - 0.5 < pos.get_x() && bloque_destructible->
                get_position().
                get_z() + 0.5 > pos.get_z() && bloque_destructible->get_position().get_z() - 0.5 < pos.get_z())
            {
                bloque_destructible->destroy();
            }
            else if (bloque_destructible == nullptr)
            // si no es un bloque destructible --> es no destructible, para la explosión.
            {
                const metal_block* bloque_no_destructible = dynamic_cast<metal_block*>(bloque.get());
                if (bloque_no_destructible != nullptr && bloque_no_destructible->get_position().get_x() + 0.5 > pos.
                    get_x() && bloque_no_destructible->get_position().get_x() - 0.5 < pos.get_x() &&
                    bloque_no_destructible->get_position().get_z() + 0.5 > pos.get_z() && bloque_no_destructible->
                    get_position().get_z() - 0.5 < pos.get_z())
                {
                    l_min = l;
                    continuar = false;
                    break;
                }
            }
        }
        if (!continuar)
            break;
    }

    //ENEMIGOS
    for (int w = k_min; w <= i_max; w++)
    {
        vector3 pos = bomb->get_position() + vector3(static_cast<float>(w), 0, 0);
        for (const auto& enemigo : enemies_)
        {
            if (enemigo->get_position().get_x() + 0.5 > pos.get_x() && enemigo->get_position().get_x() - 0.5 < pos.
                get_x()
                && enemigo->get_position().get_z() + 0.5 > pos.get_z() && enemigo->get_position().get_z() - 0.5 <
                pos.
                get_z())
            {
                enemigo->destroy();
            }
        }
    }
    for (int q = l_min; q <= j_max; q++)
    {
        vector3 pos = bomb->get_position() + vector3(0, 0, static_cast<float>(q));
        for (const auto& enemigo : enemies_)
        {
            if (enemigo->get_position().get_x() + 0.5 > pos.get_x() && enemigo->get_position().get_x() - 0.5 < pos.
                get_x()
                && enemigo->get_position().get_z() + 0.5 > pos.get_z() && enemigo->get_position().get_z() - 0.5 <
                pos.
                get_z())
            {
                enemigo->destroy();
            }
        }
    }
}

scene::scene(const int grid_width, const int grid_height, std::vector<coordinate>& brick_blocks,
             std::vector<coordinate>& metal_blocks, std::vector<coordinate>& enemies): floor_(grid(
        grid_height + 1, grid_width, block::block_size,
        vector3(0, 1, 0))),
    // Esto es re magico pero es para que aparezca en la esquina de la pantalla como en el juego
    player_(std::make_unique<player>(
        vector3(floor_.get_left(), -1, floor_.get_top() + 2))),
    camera_(new camera(player_.get()))
{
    // Initialize the grid with the specified dimensions
    const int rows = grid_height + 2;
    const int columns = grid_width;

    // Calculate starting positions to center the grid around (0, 0)
    const auto left = floor_.get_left() - 1;
    const auto top = floor_.get_top();

    // Adding walls along the borders
    for (int row = 0; row < rows; ++row)
    {
        for (int column = 0; column < columns; ++column)
        {
            if (row == 0 || row == rows - 1 || column == 0 || column == columns - 1)
            {
                // Assuming wall_block has a constructor that takes a position
                // Create position vector adjusted for centering
                auto position = vector3(left + (static_cast<float>(column) + 0.5) * block::block_size,
                                        -0.5f,
                                        top + (static_cast<float>(row) + 0.5) * block::block_size);
                auto wall = std::make_unique<wall_block>(position);
                blocks_.push_back(std::move(wall));
            }

            brick_blocks.erase(std::remove_if(brick_blocks.begin(), brick_blocks.end(),
                                              [left, column, top, row, this](const coordinate ptr)
                                              {
                                                  if (ptr.width == column && ptr.height == row)
                                                  {
                                                      auto position = vector3(
                                                          left + (static_cast<float>(column) + 0.5) * block::block_size,
                                                          -0.5f,
                                                          top + (static_cast<float>(row) + 0.5) * block::block_size);
                                                      auto brick = std::make_unique<brick_block>(position);
                                                      blocks_.push_back(std::move(brick));
                                                      return true;
                                                  }
                                                  return false;
                                              }),
                               brick_blocks.end());

            metal_blocks.erase(std::remove_if(metal_blocks.begin(), metal_blocks.end(),
                                              [left, column, top, row, this](const coordinate ptr)
                                              {
                                                  if (ptr.width == column && ptr.height == row)
                                                  {
                                                      auto position = vector3(
                                                          left + (static_cast<float>(column) + 0.5) * block::block_size,
                                                          -0.5f,
                                                          top + (static_cast<float>(row) + 0.5) * block::block_size);
                                                      auto metal = std::make_unique<metal_block>(position);
                                                      blocks_.push_back(std::move(metal));
                                                      return true;
                                                  }
                                                  return false;
                                              }),
                               metal_blocks.end());

            enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
                                         [left, column, top, row, this](const coordinate ptr)
                                         {
                                             if (ptr.width == column && ptr.height == row)
                                             {
                                                 auto position = vector3(
                                                     left + (static_cast<float>(column) + 0.5) * block::block_size,
                                                     -0.5f,
                                                     top + (static_cast<float>(row) + 0.5) * block::block_size);
                                                 enemies_.push_back(std::make_unique<enemy>(position));
                                                 return true;
                                             }
                                             return false;
                                         }),
                          enemies.end());
        }
    }
}

void scene::update_scene(const float elapsed_time)
{
    player_->move();

    for (const auto& block : blocks_)
        if (player_->check_collision(block.get()))
            player_->handle_collision(block.get());

    for (auto& enemy : enemies_)
    {
        if (player_->check_collision(enemy.get()))
            player_->handle_collision(enemy.get());
        enemy.get()->move();
    }

    update_camera();

    for (auto& bomba : bombs_)
    {
        bomba->set_timer(bomba->get_timer() - elapsed_time);
        if (bomba->get_timer() <= 0 && !bomba->is_exploded()) // si el timer llega a 0 y no ha explotado --> explota
        {
            set_off_bomb(bomba.get());
        }
    }

    blocks_.erase(std::remove_if(blocks_.begin(), blocks_.end(),
                                 [](const std::unique_ptr<block>& ptr)
                                 {
                                     return !ptr->is_active();
                                 }),
                  blocks_.end());

    enemies_.erase(std::remove_if(enemies_.begin(), enemies_.end(),
                                  [](const std::unique_ptr<enemy>& ptr)
                                  {
                                      return !ptr->is_active();
                                  }),
                   enemies_.end());

    bombs_.erase(std::remove_if(bombs_.begin(), bombs_.end(),
                                [](const std::unique_ptr<bomb>& ptr)
                                {
                                    return ptr->is_exploded();
                                }),
                 bombs_.end());
}

void scene::move_player(const vector3& displacement) const
{
    switch (camera_mode_)
    {
    case first:
        {
            const auto direction = camera_->get_direction();
            const auto position = camera_->get_position();
            const auto up = camera_->get_up();

            const auto forward = (direction - position).normalize();

            const auto forward_movement = forward * displacement.get_z();
            const auto side_movement = up * forward * displacement.get_x();

            auto movement = forward_movement + side_movement;

            movement.set_y(0);

            //if (player_->get_speed().get_x() != movement.get_x() || player_->get_speed().get_z() != movement.get_z())
            //particles_handler_->walk_particles(clock::get_total_time()/1000, player_->get_position(), player_->get_speed(), rand()%3);

            player_->set_speed(movement);

            break;
        }
    case top_down:
        {
            const auto movement = -displacement;
            //if (player_->get_speed().get_x() != movement.get_x() || player_->get_speed().get_z() != movement.get_z())
            //particles_handler_->walk_particles(clock::get_total_time()/1000, player_->get_position(), player_->get_speed(), rand()%3);
            player_->set_speed(movement);
            player_->set_direction(movement);
            break;
        }
    case perspective:
        {
            const auto movement = -displacement;
            //if (player_->get_speed().get_x() != movement.get_x() || player_->get_speed().get_z() != movement.get_z())
            //particles_handler_->walk_particles(clock::get_total_time()/1000, player_->get_position(), player_->get_speed(), rand()%3);
            player_->set_speed(movement);
            player_->set_direction(movement);
            break;
        }
    }
}

void scene::render_scene(float seconds) const
{
    lights_handler::set_light(camera_mode_, settings::get_instance()->light_color, player_->get_speed());

    gluLookAt(camera_->get_position().get_x(), camera_->get_position().get_y(), camera_->get_position().get_z(),
              camera_->get_direction().get_x(), camera_->get_direction().get_y(),
              camera_->get_direction().get_z(),
              camera_->get_up().get_x(), camera_->get_up().get_y(), camera_->get_up().get_z());


    if (camera_mode_ != first)
        renderer::draw(*player_);

    for (auto& enemy : enemies_)
        renderer::draw(*enemy.get());
    for (const auto& block : blocks_)
        renderer::draw(block->get_block(), block->get_texture());
    for (auto& bomb : bombs_)
        renderer::draw(*bomb.get());

    renderer::draw(floor_, texture_manager::grass_texture());
    if (settings::get_instance()->textures_enabled)
        renderer::draw_skybox(skybox_);

    renderer::draw(seconds, particles_handler_);
    lights_handler::disable_light();
}

camera_mode scene::get_camera_mode() const
{
    return camera_mode_;
}

camera* scene::get_camera() const
{
    return camera_;
}

void scene::drop_bomb()
{
    vector3 player_position = player_->get_position();
    player_position.set_y(-0.5);
    bombs_.emplace_back(std::make_unique<bomb>(player_position));
}

grid scene::get_floor() const
{
    return floor_;
}

scene scene::level1()
{
    std::vector<coordinate> brick_blocks = {
        {1, 6}, {1, 7}, {1, 8}, {1, 10}, {1, 11}, {1, 12}, {1, 13}, {1, 14},
        {3, 10}, {3, 12}, {3, 15},
        {4, 1}, {4, 11},
        {5, 11},
        {7, 1}, {7, 5}, {7, 14},
        {8, 9},
        {9, 6}, {9, 7},
        {10, 3}, {10, 13},
        {11, 9}
    };

    std::vector<coordinate> metal_blocks = {
        {2, 2}, {2, 4}, {2, 6}, {2, 8}, {2, 10}, {2, 12}, {2, 14},
        {4, 2}, {4, 4}, {4, 6}, {4, 8}, {4, 10}, {4, 12}, {4, 14},
        {6, 2}, {6, 4}, {6, 6}, {6, 8}, {6, 10}, {6, 12}, {6, 14},
        {8, 2}, {8, 4}, {8, 6}, {8, 8}, {8, 10}, {8, 12}, {8, 14},
        {10, 2}, {10, 4}, {10, 6}, {10, 8}, {10, 10}, {10, 12}, {10, 14},
    };

    std::vector<coordinate> enemies = {
        {3, 9},
        {10, 11},
        {11, 14}
    };

    return scene(17, 11, brick_blocks, metal_blocks, enemies);
}
