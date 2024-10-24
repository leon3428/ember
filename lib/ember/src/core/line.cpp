#include "line.hpp"

ember::Line::Line() : m_length(1.0f) {}
ember::Line::Line(float length) : m_length(length) {}

auto ember::Line::getPosition(float t) const -> Eigen::Vector3f { return {0.0f, 0.0f, t * m_length}; }