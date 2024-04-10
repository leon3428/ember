#ifndef FPS_CAMERA_CONTROLLER
#define FPS_CAMERA_CONTROLLER

#include "../core/transform.hpp"
#include "../core/window.hpp"
#include "perspective_camera.hpp"

namespace ember {

class FpsCameraController {
 public:
  FpsCameraController(PerspectiveCamera &camera, Window &window);

  auto update(float deltaTime) -> void;

 private:
  PerspectiveCamera &m_camera;
  Window &m_window;

  float m_yaw;
  float m_pitch;

  float m_lastMouseX;
  float m_lastMouseY;
};

}  // namespace ember

#endif  // FPS_CAMERA_CONTROLLER