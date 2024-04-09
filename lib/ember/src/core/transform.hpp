#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <glm/glm.hpp>

namespace ember {

struct Transform {

  Transform();

  [[nodiscard]] auto getMatrix() const -> glm::mat4;
  [[nodiscard]] auto getInverse() const -> glm::mat4;

  glm::vec3 position;
  glm::vec3 scale;
  glm::mat4 rotation;
};

}  // namespace ember

#endif  // TRANSFORM_HPP