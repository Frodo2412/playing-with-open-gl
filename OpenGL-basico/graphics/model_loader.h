#pragma once
#include <assimp/Importer.hpp>

class model_loader
{
    static Assimp::Importer importer_;

public:
    static aiScene* load_model(const std::string& file_path);
};
