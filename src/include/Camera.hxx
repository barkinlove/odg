#pragma once
#include <glm/vec3.hpp>

class Camera final
{
public:
  explicit Camera(glm::vec3 pos);

private:
  glm::vec3 m_pos;
};
