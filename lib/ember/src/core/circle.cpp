#include "circle.hpp"
#include <numbers>

ember::Circle::Circle() : m_radius(0.0f) {}
ember::Circle::Circle(float radius) : m_radius(radius) {}

auto ember::Circle::getPosition(float t) const -> Eigen::Vector3f {
  auto x = m_radius * cosf(t * 2.0f * std::numbers::pi_v<float>);
  auto y = m_radius * sinf(t * 2.0f * std::numbers::pi_v<float>);

  return {x, 0.0f, y};
}