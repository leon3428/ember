#ifndef PERSPECTIVE_CAMERA_HPP
#define PERSPECTIVE_CAMERA_HPP

#include <glm/glm.hpp>
#include "camera.hpp"

namespace ember {

class PerspectiveCamera : public ICamera {
 public:
  PerspectiveCamera(float fov, float nearPlane, float farPlane);

  [[nodiscard]] virtual auto getProjectionMatrix(int width, int height) const -> glm::mat4 override;
 private:
  float m_fov;
  float m_nearPlane;
  float m_farPlane;
};

}  // namespace ember

#endif  // PERSPECTIVE_CAMERA_HPP