#pragma once
#include <vector>

#include "game_object.h"
#include "../graphics/model_loader.h"
#include "../graphics/vertex.h"
#include "../textures/texture.h"

enum rotation
{
    up,right,down,left
};

class entity : public game_object
{
    std::vector<vertex> vertices_;
    vector3 direction_, up_;
    aabb bounding_box_;
    float scale_factor_ = 1.0f;
    float last_rotation_;
    rotation new_rotation_;

protected:
    vector3 speed_;

    ~entity() = default;

public:
    bool is_player_ = false;
    explicit entity(const std::string& file_path, const texture texture, const float hitbox_size,
                    const vector3& position = vector3(0, -0.75, 0),
                    const vector3& direction = vector3(0, 0, 5),
                    const vector3& up = vector3(0, 1, 0)): game_object(position, texture),
                                                           vertices_(model_loader::load_model(file_path)),
                                                           direction_(direction),
                                                           up_(up), speed_(vector3(0, 0, 0))
    {
        float min_x = std::numeric_limits<float>::max();
        float max_x = std::numeric_limits<float>::lowest();
        float min_y = std::numeric_limits<float>::max();
        float max_y = std::numeric_limits<float>::lowest();
        float min_z = std::numeric_limits<float>::max();
        float max_z = std::numeric_limits<float>::lowest();

        for (const auto& vertex : vertices_)
        {
            min_x = std::min(min_x, vertex.position.get_x());
            max_x = std::max(max_x, vertex.position.get_x());
            min_y = std::min(min_y, vertex.position.get_y());
            max_y = std::max(max_y, vertex.position.get_y());
            min_z = std::min(min_z, vertex.position.get_z());
            max_z = std::max(max_z, vertex.position.get_z());
        }

        const float model_width = max_x - min_x;
        const float model_height = max_y - min_y;
        const float model_depth = max_z - min_z;

        float scale_x = hitbox_size / model_width;
        float scale_y = hitbox_size / model_height;
        float scale_z = hitbox_size / model_depth;

        scale_factor_ = std::min({scale_x, scale_y, scale_z});
        bounding_box_ = {vector3(min_x, min_y, min_z) * scale_factor_, vector3(max_x, max_y, max_z) * scale_factor_};
        last_rotation_ = 90;
        new_rotation_ = down;
    }

    std::vector<vertex> get_vertices() const;

    vector3 get_direction() const;
    vector3 get_up() const;

    void set_direction(const vector3& direction);
    void set_position(const vector3& position);
    void set_speed(const vector3& speed);
    void move();

    float get_scale_factor() const;

    virtual void handle_collision(game_object* other) = 0;

    bool check_collision(const game_object* other_object) const;

    aabb get_bounding_box() const override;

    float get_last_rotation();
    void set_last_rotation(float last_rotation);
    void set_new_rotation(rotation new_rotation);
    rotation get_new_rotation();
    bool get_is_player_();
};
