#include "camera.hpp"
#include "../core/utils.hpp"
#include "glm/geometric.hpp"
#include "glm/gtc/quaternion.hpp"
#include "node.hpp"

ember::Camera::Camera() { m_attributes |= static_cast<unsigned>(NodeAttribute::Camera); }

auto ember::Camera::lookAt(glm::vec3 target) -> void {
  auto dir = glm::normalize(target - getPosition());

  auto tmp = glm::quatLookAt(dir, yAxis);
  setRotation(tmp);
}