#pragma once
#include "RGB.hxx"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

struct Vertex
{
  glm::vec3 pos;
  glm::vec3 normal;
  glm::vec2 texture;
  RGB color;
};

static_assert(sizeof(Vertex) == 44);
