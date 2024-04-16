#pragma once
#include <vector>
#include <assimp/Importer.hpp>

#include "vertex.h"

class model_loader
{
    static Assimp::Importer importer_;

public:
    static std::vector<vertex> load_model(const std::string& file_path);
};
