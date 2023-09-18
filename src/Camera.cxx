#include "Camera.hxx"
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <utility>

Camera::Camera()
  : m_pos{ 0.f, 0.f, 3.f }
  , m_front{ 0.f, 0.f, -1.f }
  , m_up{ 0.f, 1.f, 0.f }
  , m_angles{ 0.f, 0.f, 0.f }
  , m_speed{ 0.005f }
{
}

void Camera::set_pos(glm::vec3 pos) noexcept
{
  m_pos = std::move(pos);
}

void Camera::set_front(glm::vec3 front) noexcept
{
  m_front = std::move(front);
}

void Camera::set_up(glm::vec3 up) noexcept
{
  m_up = std::move(up);
}

glm::mat4x4 Camera::get_view() noexcept
{

  glm::vec3 direction;
  // x -> pitch
  // y -> yaw
  // z -> roll
  direction.x =
    std::cos(glm::radians(m_angles.y)) * std::cos(glm::radians(m_angles.x));
  direction.y = std::sin(glm::radians(m_angles.x));
  direction.z =
    std::sin(glm::radians(m_angles.y)) * std::cos(glm::radians(m_angles.x));
  m_front = glm::normalize(direction);
  return glm::lookAt(m_pos, m_pos + m_front, m_up);
}

float Camera::get_speed() const noexcept
{
  return m_speed;
}

void Camera::set_speed(float speed) noexcept
{
  m_speed = speed;
}

namespace {

float calculateSpeed(float speed, uint32_t acceleration)
{
  return speed * acceleration;
}

}

void Camera::move_forward() noexcept
{
  m_pos += calculateSpeed(m_speed, m_acceleration) * m_front;
}

void Camera::move_backward() noexcept
{
  m_pos -= calculateSpeed(m_speed, m_acceleration) * m_front;
}

void Camera::move_right() noexcept
{
  m_pos += glm::normalize(glm::cross(m_front, m_up)) *
           calculateSpeed(m_speed, m_acceleration);
}

void Camera::move_left() noexcept
{
  m_pos += glm::normalize(glm::cross(m_up, m_front)) *
           calculateSpeed(m_speed, m_acceleration);
}

void Camera::set_angles(glm::vec3 angles) noexcept
{
  m_angles = std::move(angles);
}

void Camera::set_acceleration(uint32_t acceleration) noexcept
{
  m_acceleration = acceleration;
}

void Camera::increase_pitch() noexcept
{
  if (m_angles.x > 90.f) {
    m_angles.x = 90.f;
  } else {
    m_angles.x += 1.f;
  }
}

void Camera::decrease_pitch() noexcept
{
  if (m_angles.x < -90.f) {
    m_angles.x = -90.f;
  } else {
    m_angles.x -= 1.f;
  }
}

void Camera::incraese_yaw() noexcept
{
  m_angles.y += 1.f;
}

void Camera::decrease_yaw() noexcept
{
  m_angles.y -= 1.f;
}
