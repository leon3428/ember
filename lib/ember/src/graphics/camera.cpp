#include "camera.hpp"
#include "node.hpp"

ember::Camera::Camera() {
  m_attributes |= static_cast<unsigned>(NodeAttribute::Camera);
}