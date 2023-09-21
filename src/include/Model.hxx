#pragma once
#include "Mesh.hxx"
#include <string_view>

struct Model
{
  std::vector<Mesh> meshes;
};
