#pragma once
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class Camera final
{
public:
  Camera();

  void move_forward() noexcept;
  void move_backward() noexcept;
  void move_right() noexcept;
  void move_left() noexcept;
  void set_pos(glm::vec3 pos) noexcept;
  void set_front(glm::vec3 direction) noexcept;
  void set_up(glm::vec3 up) noexcept;
  void set_speed(float speed) noexcept;
  void set_acceleration(uint32_t accelration) noexcept;
  float get_speed() const noexcept;
  void set_angles(glm::vec3 angles) noexcept;
  void increase_pitch() noexcept;
  void decrease_pitch() noexcept;
  void incraese_yaw() noexcept;
  void decrease_yaw() noexcept;
  glm::mat4x4 get_view() noexcept;

private:
  glm::vec3 m_pos;
  glm::vec3 m_front;
  glm::vec3 m_up;
  glm::vec3 m_angles;
  // mb it's worth making it float
  uint32_t m_acceleration;
  float m_speed;
};
