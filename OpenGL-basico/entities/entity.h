#pragma once
#include <vector>

#include "../graphics/model_loader.h"
#include "../graphics/vertex.h"

class entity
{
    std::vector<vertex> vertices_;

protected:
    std::string file_path_;

public:
    explicit entity(std::string file_path): file_path_(std::move(file_path))
    {
        vertices_ = model_loader::load_model(file_path_);
    }
};
