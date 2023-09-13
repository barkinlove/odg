#pragma once

class Math final
{
public:
  static float to_rad(float degrees) noexcept;
  static float to_deg(float radians) noexcept;

private:
  static float m_pi;
};
