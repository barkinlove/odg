#include "Loader.hxx"
#include "Mesh.hxx"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <spdlog/spdlog.h>

#include <iostream>

namespace {

Mesh process_mesh(aiMesh* mesh /* const aiScene* scene */)
{
  std::vector<Vertex> vertices;
  std::vector<std::uint32_t> indices;
  std::vector<Texture> texture;
  vertices.reserve(mesh->mNumVertices);
  for (std::size_t i = 0; i < mesh->mNumVertices; ++i) {
    Vertex vertex;
    vertex.pos.x = mesh->mVertices[i].x;
    vertex.pos.y = mesh->mVertices[i].y;
    vertex.pos.z = mesh->mVertices[i].z;
    vertex.normal.x = mesh->mNormals[i].x;
    vertex.normal.y = mesh->mNormals[i].y;
    vertex.normal.z = mesh->mNormals[i].z;

    vertex.color.red = mesh->mColors[0][i].r;
    vertex.color.green = mesh->mColors[0][i].g;
    vertex.color.blue = mesh->mColors[0][i].b;

    // object has no texture and now this casuses to segfault
    // vertex.texture.x = mesh->mTextureCoords[i]->x;
    // vertex.texture.y = mesh->mTextureCoords[i]->y;
    vertices.push_back(std::move(vertex));
  }
  indices.reserve(mesh->mNumFaces * mesh->mFaces[0].mNumIndices);
  for (std::size_t i = 0; i < mesh->mNumFaces; ++i) {
    for (std::size_t j = 0; j < mesh->mFaces[i].mNumIndices; ++j) {
      indices.push_back(mesh->mFaces[i].mIndices[j]);
    }
  }
  // mb implement material?
  return { vertices, indices, texture };
}

void process_node(Model& model, aiNode* node, const aiScene* scene)
{
  for (std::size_t i = 0; i < node->mNumMeshes; ++i) {
    aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
    model.meshes.push_back(process_mesh(mesh));
  }

  for (std::size_t i = 0; i < node->mNumChildren; ++i) {
    process_node(model, node->mChildren[i], scene);
  }
}

}

Model Loader::load_model(std::string_view path)
{
  Assimp::Importer importer;
  const aiScene* scene =
    importer.ReadFile(path.data(), aiProcess_Triangulate | aiProcess_FlipUVs);
  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
      !scene->mRootNode) {
    throw std::runtime_error(importer.GetErrorString());
  }
  Model model;
  model.meshes.reserve(scene->mRootNode->mNumMeshes);
  process_node(model, scene->mRootNode, scene);
  return model;
}
