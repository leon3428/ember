#include "object3d.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include "node.hpp"

ember::Object3d::Object3d() : position(0.0f), scale(1.0f), rotation(1.0f) {
  m_attributes |= static_cast<unsigned>(NodeAttribute::Object3d);
}

auto ember::Object3d::getMatrix() const -> glm::mat4 {
  glm::mat4 ret(1.0f);

  ret = glm::translate(ret, position);
  ret = ret * rotation;
  ret = glm::scale(ret, scale);

  return ret;
}

auto ember::Object3d::getInverse() const -> glm::mat4 { return glm::inverse(getMatrix()); }
