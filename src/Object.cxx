#include "Object.hxx"
#include <glm/ext/matrix_transform.hpp>

Object::Object()
  : m_scale{ 0.5f, 0.5f, 0.5f }
{
}

glm::mat4x4 Object::get_transformation() const noexcept
{
  auto res = glm::scale(glm::identity<glm::mat4x4>(), m_scale);
  res = glm::rotate(res, m_rotation[0], glm::vec3{ 1.f, 0.f, 0.f });
  res = glm::rotate(res, m_rotation[1], glm::vec3{ 0.f, 1.f, 0.f });
  res = glm::rotate(res, m_rotation[2], glm::vec3{ 0.f, 0.f, 1.f });
  return glm::translate(res, m_pos);
}

const glm::vec3& Object::get_pos() const noexcept
{
  return m_pos;
}

const glm::vec3& Object::get_rotation() const noexcept
{
  return m_rotation;
}

const glm::vec3& Object::get_scale() const noexcept
{
  return m_scale;
}

void Object::move(glm::vec3 newPos) noexcept
{
  m_pos = std::move(newPos);
}

void Object::move_x(float value) noexcept
{
  m_pos[0] = value;
}

void Object::move_y(float value) noexcept
{
  m_pos[1] = value;
}

void Object::move_z(float value) noexcept
{
  m_pos[2] = value;
}

void Object::scale(glm::vec3 scalars) noexcept
{
  m_scale = std::move(scalars);
}

void Object::scale_x(float scalar) noexcept
{
  m_scale[0] = scalar;
}

void Object::scale_y(float scalar) noexcept
{
  m_scale[1] = scalar;
}

void Object::scale_z(float scalar) noexcept
{
  m_scale[2] = scalar;
}

void Object::rotate(glm::vec3 angles) noexcept
{
  m_rotation = std::move(angles);
}

void Object::rotate_x(float angle) noexcept
{
  m_rotation[0] = angle;
}

void Object::rotate_y(float angle) noexcept
{
  m_rotation[1] = angle;
}

void Object::rotate_z(float angle) noexcept
{
  m_rotation[2] = angle;
}
