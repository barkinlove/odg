#pragma once
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class Object
{
public:
  Object();

  void move(glm::vec3 newPos) noexcept;
  void rotate(glm::vec3 angles) noexcept;
  void scale(glm::vec3 scalars) noexcept;
  void move_x(float newX) noexcept;
  void move_y(float newY) noexcept;
  void move_z(float newZ) noexcept;
  void rotate_x(float alpha) noexcept;
  void rotate_y(float beta) noexcept;
  void rotate_z(float ghama) noexcept;
  void scale_x(float scalar) noexcept;
  void scale_y(float scalar) noexcept;
  void scale_z(float scalar) noexcept;
  [[nodiscard]] glm::mat4x4 get_transformation() const noexcept;
  [[nodiscard]] const glm::vec3& get_pos() const noexcept;
  [[nodiscard]] const glm::vec3& get_scale() const noexcept;
  [[nodiscard]] const glm::vec3& get_rotation() const noexcept;

private:
  glm::vec3 m_pos;
  glm::vec3 m_scale;
  glm::vec3 m_rotation;
};
