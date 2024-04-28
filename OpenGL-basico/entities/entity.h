#pragma once
#include <vector>

#include "game_object.h"
#include "../graphics/model_loader.h"
#include "../graphics/vertex.h"
#include "../textures/texture.h"
#include "../textures/texture_loader.h"

class entity : public game_object
{
protected:
    ~entity() = default;

private:
    std::vector<vertex> vertices_;
    vector3 direction_, up_;
    float scale_factor_ = 1.0f;
    aabb bounding_box_;

public:
    explicit entity(const std::string& file_path, const texture texture, const float hitbox_size,
                    const vector3& position = vector3(0, 0, 0),
                    const vector3& direction = vector3(1, 0, 0),
                    const vector3& up = vector3(0, 1, 0)): game_object(position, texture),
                                                           vertices_(model_loader::load_model(file_path)),
                                                           direction_(direction),
                                                           up_(up)
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
    }

    std::vector<vertex> get_vertices() const;
    texture get_texture() const;

    vector3 get_direction() const;
    vector3 get_up() const;

    void set_direction(const vector3& direction);
    void set_position(const vector3& position);

    void move(const vector3& displacement);
    float get_scale_factor() const;

    aabb get_bounding_box() override;
};
