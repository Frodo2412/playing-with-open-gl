#pragma once
#include <vector>

#include "../graphics/model_loader.h"
#include "../graphics/vertex.h"
#include "../textures/texture.h"
#include "../textures/texture_loader.h"

class entity
{
    std::vector<vertex> vertices_;
    vector3 position_, direction_, up_;
    texture texture_;

public:
    explicit entity(const std::string& file_path, const char* texture_path, const vector3& position = vector3(0, 0, 0),
                    const vector3& direction = vector3(1, 0, 0),
                    const vector3& up = vector3(0, 1, 0)): vertices_(model_loader::load_model(file_path)),
                                                           position_(position),
                                                           direction_(direction),
                                                           up_(up), texture_(texture_loader::load_texture(texture_path))
    {
    }

    std::vector<vertex> get_vertices() const;
    texture get_texture() const;

    vector3 get_position() const;
    vector3 get_direction() const;
    vector3 get_up() const;

    void set_direction(const vector3& direction);
    void set_position(const vector3& position);

    void move(const vector3& displacement);
};
