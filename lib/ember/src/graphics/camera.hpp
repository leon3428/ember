#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>

namespace ember {

class ICamera {
 public:
  [[nodiscard]] virtual auto getProjectionMatrix(int width, int height) const -> glm::mat4 = 0;
  [[nodiscard]] virtual auto getViewMatrix() const -> glm::mat4 = 0;

 protected:
  ~ICamera() = default;
};

}  // namespace ember

#endif  // CAMERA_HPP