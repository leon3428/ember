#include "fps_camera_controller.hpp"

#include <glm/gtc/matrix_transform.hpp>

ember::FpsCameraController::FpsCameraController(PerspectiveCamera &camera, Window &window)
    : m_camera(camera),
      m_window(window),
      m_yaw(-glm::pi<float>() / 2.0f),
      m_pitch(0),
      m_lastMouseX(0),
      m_lastMouseY(0) {}

auto ember::FpsCameraController::update(float deltaTime) -> void {
  if (m_window.isKeyPressed(KeyCode::KeyW)) {
    m_camera.pos += (0.01f * deltaTime) * m_camera.direction;
  }
  if (m_window.isKeyPressed(KeyCode::KeyS)) {
    m_camera.pos -= (0.01f * deltaTime) * m_camera.direction;
  }
  if (m_window.isKeyPressed(KeyCode::KeyD)) {
    m_camera.pos += (0.01f * deltaTime) * glm::normalize(glm::cross(m_camera.direction, m_camera.up));
  }
  if (m_window.isKeyPressed(KeyCode::KeyA)) {
    m_camera.pos -= (0.01f * deltaTime) * glm::normalize(glm::cross(m_camera.direction, m_camera.up));
  }
  if (m_window.isKeyPressed(KeyCode::KeyLeftControl)) {
    auto right = glm::cross(m_camera.direction, m_camera.up);
    m_camera.pos += (0.01f * deltaTime) * glm::normalize(glm::cross(m_camera.direction, right));
  }
  if (m_window.isKeyPressed(KeyCode::KeyLeftShift)) {
    auto right = glm::cross(m_camera.direction, m_camera.up);
    m_camera.pos -= (0.01f * deltaTime) * glm::normalize(glm::cross(m_camera.direction, right));
  }

  auto [mouseX, mouseY] = m_window.getMousePos();

  if (m_window.isMouseButtonPressed(MouseButtonCode::MouseButtonLeft)) {
    auto deltaX = mouseX - m_lastMouseX;
    auto deltaY = mouseY - m_lastMouseY;

    m_yaw += 0.0001f * deltaTime * deltaX;
    m_pitch -= 0.0001f * deltaTime * deltaY;

    m_camera.direction.x = cos(m_yaw) * cos(m_pitch);
    m_camera.direction.y = sin(m_pitch);
    m_camera.direction.z = sin(m_yaw) * cos(m_pitch);
    m_camera.direction = glm::normalize(m_camera.direction);
  }

  m_lastMouseX = mouseX;
  m_lastMouseY = mouseY;
}
