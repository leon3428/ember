#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include "object3d.hpp"

namespace ember {

class Camera : public Object3d {
 public:
  Camera();

  [[nodiscard]] virtual auto getProjectionMatrix(int width, int height) const -> glm::mat4 = 0;
  [[nodiscard]] virtual auto getViewMatrix() const -> glm::mat4 = 0;

 protected:
  ~Camera() = default;
};

}  // namespace ember

#endif  // CAMERA_HPP