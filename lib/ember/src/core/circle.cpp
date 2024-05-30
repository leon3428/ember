#include "circle.hpp"
#include <numbers>

ember::Circle::Circle() : m_radius(0.0f) {}
ember::Circle::Circle(float radius) : m_radius(radius) {}

auto ember::Circle::getPosition(float t) const -> Eigen::Vector3f {
  auto x = m_radius * cos(t * 2.0 * std::numbers::pi);
  auto y = m_radius * sin(t * 2.0 * std::numbers::pi);

  return {x, 0.0f, y};
}