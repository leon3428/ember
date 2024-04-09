#include "transform.hpp"

#include <glm/gtc/matrix_transform.hpp>

ember::Transform::Transform() : position(0.0f), scale(1.0f), rotation(1.0f) {}

auto ember::Transform::getMatrix() const -> glm::mat4 {
  glm::mat4 ret(1.0f);

  ret = glm::scale(ret, scale);
  ret = rotation * glm::scale(ret, scale);

  return glm::translate(ret, position);
}

auto ember::Transform::getInverse() const -> glm::mat4 {
  return glm::inverse(getMatrix());
}
