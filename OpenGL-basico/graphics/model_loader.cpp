#include "model_loader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>

#include "../textures/texture.h"

Assimp::Importer model_loader::importer_;

void process_mesh(const aiMesh* mesh, std::vector<vertex>& vertices,
                  std::vector<unsigned int>& indices)
{
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        auto position = vector3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        auto normal = vector3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
        vector2 texture;
        if (mesh->mTextureCoords[0]) texture = vector2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
        else texture = vector2(0.0f, 0.0f);


        vertices.emplace_back(position, normal, texture);
    }

    // Indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        const aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
}


void process_node(const aiNode* node, const aiScene* scene, std::vector<vertex>& vertices,
                  std::vector<unsigned int>& indices)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        const aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        process_mesh(mesh, vertices, indices);
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        process_node(node->mChildren[i], scene, vertices, indices);
    }
}

std::vector<vertex> model_loader::load_model(const std::string& file_path)
{
    const aiScene* scene = importer_.ReadFile(file_path,
                                              aiProcess_Triangulate |
                                              aiProcess_FlipUVs |
                                              aiProcess_GenNormals);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        // Error handling
        std::cerr << "ERROR::ASSIMP::" << importer_.GetErrorString() << '\n';
        throw std::runtime_error("Error loading model");
    }

    std::vector<vertex> vertices;
    std::vector<unsigned int> indices;

    process_node(scene->mRootNode, scene, vertices, indices);

    return vertices;
}
