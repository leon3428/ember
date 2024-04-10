#include "transform.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "my_glm.hpp"

ember::Transform::Transform() : position(0.0f), scale(1.0f), rotation(1.0f) {}

auto ember::Transform::getMatrix() const -> glm::mat4 {
  glm::mat4 ret = my_glm::translate3D(position);
  ret *= rotation;
  ret *= my_glm::scale3D(scale);

  return ret;
}

auto ember::Transform::getInverse() const -> glm::mat4 { return glm::inverse(getMatrix()); }
