#include "Math.hxx"
#include <cmath>

float Math::m_pi = std::acos(-1.f);

float Math::to_deg(float radians) noexcept
{
  return radians * 180.f / m_pi;
}

float Math::to_rad(float degrees) noexcept
{
  return degrees * m_pi / 180.f;
}
