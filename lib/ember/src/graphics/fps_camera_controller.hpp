#ifndef FPS_CAMERA_CONTROLLER
#define FPS_CAMERA_CONTROLLER

#include "../core/window.hpp"
#include "../core/transform.hpp"

namespace ember {

class FpsCameraController {
 public:
  FpsCameraController(Window &window, Transform &cameraTransform);

  auto update(float deltaTime) -> void;

 private:
  Window &m_window;
  Transform &m_cameraTransform;

  float m_lastMouseX;
  float m_lastMouseY;
};

}  // namespace ember

#endif  // FPS_CAMERA_CONTROLLER