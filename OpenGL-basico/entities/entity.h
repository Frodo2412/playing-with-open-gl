#pragma once
#include <vector>

#include "../graphics/model_loader.h"
#include "../graphics/vertex.h"
#include "../textures/texture.h"
#include "../textures/texture_loader.h"

class entity
{
    std::vector<vertex> vertices_;
    texture texture_;

public:
    explicit entity(const std::string& file_path, const char* texture_path):
        vertices_(model_loader::load_model(file_path)), texture_(texture_loader::load_texture(texture_path))
    {
    }

    std::vector<vertex> get_vertices() const;
    texture get_texture() const;
};
