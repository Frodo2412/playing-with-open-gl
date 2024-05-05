#include "scene.h"

#include <GL/glu.h>

#include "../entities/bomb.h"
#include "../utils/renderer.h"
#include "../interfaces/settings.h"
#include "../utils/lights_handler.h"

constexpr auto rango_horizontal = 3;
constexpr auto rango_vertical = 3;
const auto settings = settings::get_instance();

void scene::toggle_camera()
{
    switch (camera_mode_)
    {
    case first:
        camera_mode_ = top_down;
        camera_->set_position(vector3(0, 10, 0));
        camera_->set_direction(vector3(0, 0, 0));
        camera_->set_up(vector3(0, 0, -1));
        break;
    case top_down:
        {
            camera_mode_ = perspective;
            const auto player_position = player_->get_position();
            camera_->set_position(player_position + vector3(0, 5, 5));
            camera_->set_direction(player_position);
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
        camera_->move(player_->get_speed());
        break;
    case perspective:
        camera_->move(player_->get_speed());
        break;
    case top_down:
        break;
    }
}

void scene::set_off_bomb(bomb* bomb) const
{
    bomb->explotar();
    bool continuar = true;

    int i_max = rango_horizontal;
    int k_min = -rango_horizontal;
    int j_max = rango_vertical;
    int l_min = -rango_vertical;

    //ROMPER HORIZONTAL
    for (int i = 0; i <= rango_horizontal; i++)
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
    for (int k = -rango_horizontal; k < 0; k++)
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
    for (int j = 0; j <= rango_vertical; j++)
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
    for (int l = -rango_vertical; l < 0; l++)
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

void scene::update_scene(const float elapsed_time)
{
    player_->move();

    for (const auto& block : blocks_)
    {
        if (player_->check_collision(block.get()))
        {
            player_->handle_collision(block.get());
        }
    }
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

            player_->set_speed(movement);
            break;
        }
    case top_down:
        {
            const auto movement = -displacement;
            player_->set_speed(movement);
            player_->set_direction(movement);
            break;
        }
    case perspective:
        {
            const auto movement = -displacement;
            player_->set_speed(movement);
            player_->set_direction(movement);
            break;
        }
    }
}

void scene::render_scene() const
{
    lights_handler::set_light(camera_mode_, settings::get_instance()->light_color, player_->get_speed());

    gluLookAt(camera_->get_position().get_x(), camera_->get_position().get_y(), camera_->get_position().get_z(),
              camera_->get_direction().get_x(), camera_->get_direction().get_y(),
              camera_->get_direction().get_z(),
              camera_->get_up().get_x(), camera_->get_up().get_y(), camera_->get_up().get_z());


    if(camera_mode_ != first)
        renderer::draw(*player_);

    for (auto& enemy : enemies_)
        renderer::draw(*enemy.get());
    for (const auto& block : blocks_)
        renderer::draw(block->get_block(), block->get_texture());
    for (auto& bomb : bombs_)
        renderer::draw(*bomb.get());

    renderer::draw(floor_, texture_manager::grass_texture());

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
    bombs_.emplace_back(std::make_unique<bomb>(player_->get_position()));
    player_position.set_y(-0.5);
}

grid scene::get_floor() const
{
    return floor_;
}
