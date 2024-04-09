#include "fps_camera_controller.hpp"

#include <glm/gtc/matrix_transform.hpp>

ember::FpsCameraController::FpsCameraController(Window &window, Transform &cameraTransform)
    : m_window(window), m_cameraTransform(cameraTransform), m_lastMouseX(0), m_lastMouseY(0) {}

auto ember::FpsCameraController::update(float deltaTime) -> void {
  if (m_window.isKeyPressed(KeyCode::KeyW)) {
    m_cameraTransform.position.z += 0.01 * deltaTime;
  }
  if (m_window.isKeyPressed(KeyCode::KeyS)) {
    m_cameraTransform.position.z -= 0.01 * deltaTime;
  }
  if (m_window.isKeyPressed(KeyCode::KeyA)) {
    m_cameraTransform.position.x += 0.01 * deltaTime;
  }
  if (m_window.isKeyPressed(KeyCode::KeyD)) {
    m_cameraTransform.position.x -= 0.01 * deltaTime;
  }
  if (m_window.isKeyPressed(KeyCode::KeyLeftControl)) {
    m_cameraTransform.position.y += 0.01 * deltaTime;
  }
  if (m_window.isKeyPressed(KeyCode::KeyLeftShift)) {
    m_cameraTransform.position.y -= 0.01 * deltaTime;
  }

  auto [mouseX, mouseY] = m_window.getMousePos();

  if (m_window.isMouseButtonPressed(MouseButtonCode::MouseButtonLeft)) {
    auto deltaX = mouseX - m_lastMouseX;
    auto deltaY = mouseY - m_lastMouseY;

    m_cameraTransform.rotation = glm::rotate(m_cameraTransform.rotation, 0.001f * deltaX, {0.0, 1.0, 0.0});
    m_cameraTransform.rotation = glm::rotate(m_cameraTransform.rotation, 0.001f * deltaY, {1.0, 0.0, 0.0});
  }

  m_lastMouseX = mouseX;
  m_lastMouseY = mouseY;
}
