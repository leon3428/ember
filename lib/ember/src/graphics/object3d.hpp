#ifndef OBJECT_3D_HPP
#define OBJECT_3D_HPP

#include <glm/glm.hpp>
#include "node.hpp"

namespace ember {

class Object3d : public Node {
 public:
  Object3d();
  virtual ~Object3d() = default;

  [[nodiscard]] auto getMatrix() const -> glm::mat4;
  [[nodiscard]] auto getInverse() const -> glm::mat4;

  glm::vec3 position;
  glm::vec3 scale;
  glm::mat4 rotation;
};

}  // namespace ember

#endif  // OBJECT_3D_HPP