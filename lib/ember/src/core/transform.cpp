#include "transform.hpp"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

ember::Transform::Transform() : position(0.0f), scale(1.0f), rotation(1.0f) {}

auto ember::Transform::getMatrix() const -> glm::mat4 {
  glm::mat4 ret(1.0f);

  // for(int i = 0;i < 4; i++) {
  //   for(int j = 0;j < 4; j++) {
  //     std::cout << ret[i][j] << ' ';
  //   }
  //   std::cout << '\n';
  // }
  // std::cout << '\n';
  
  ret = glm::translate(ret, position);
  ret = ret * rotation;
  ret = glm::scale(ret, scale);

  return ret;
}

auto ember::Transform::getInverse() const -> glm::mat4 {
  return glm::inverse(getMatrix());
}
