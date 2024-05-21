#ifndef FPS_CAMERA_CONTROLLER
#define FPS_CAMERA_CONTROLLER

#include "../core/window.hpp"
#include "camera.hpp"

namespace ember {

class FpsCameraController {
 public:
  FpsCameraController(Camera *camera, Window &window);

  auto update(float deltaTime) -> void;

 private:
  Camera *m_camera;
  Window &m_window;

  float m_moveSpeed;
  float m_turnSpeed;

  float m_lastMouseX;
  float m_lastMouseY;
};

}  // namespace ember

#endif  // FPS_CAMERA_CONTROLLER