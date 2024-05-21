#include "fps_camera_controller.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include "../core/utils.hpp"
#include "glm/ext/quaternion_trigonometric.hpp"
#include "glm/gtc/quaternion.hpp"

ember::FpsCameraController::FpsCameraController(Camera *camera, Window &window)
    : m_camera(camera), m_window(window), m_moveSpeed(0.01f), m_turnSpeed(0.0001f), m_lastMouseX(0), m_lastMouseY(0) {}

auto ember::FpsCameraController::update(float deltaTime) -> void {
  auto [mouseX, mouseY] = m_window.getMousePos();

  auto rotMat = glm::mat4_cast(m_camera->rotation);
  auto right = glm::vec3(rotMat[0][0], rotMat[1][0], rotMat[2][0]);    // First column
  auto up = glm::vec3(rotMat[0][1], rotMat[1][1], rotMat[2][1]);       // Second column
  auto forward = glm::vec3(rotMat[0][2], rotMat[1][2], rotMat[2][2]);  // Third column

  if (m_window.isKeyPressed(KeyCode::KeyW)) {
    m_camera->position += (m_moveSpeed * deltaTime) * forward;
  }
  if (m_window.isKeyPressed(KeyCode::KeyS)) {
    m_camera->position -= (m_moveSpeed * deltaTime) * forward;
  }
  if (m_window.isKeyPressed(KeyCode::KeyA)) {
    m_camera->position += (m_moveSpeed * deltaTime) * right;
  }
  if (m_window.isKeyPressed(KeyCode::KeyD)) {
    m_camera->position -= (m_moveSpeed * deltaTime) * right;
  }
  if (m_window.isKeyPressed(KeyCode::KeyLeftShift)) {
    m_camera->position += (m_moveSpeed * deltaTime) * yAxis;
  }
  if (m_window.isKeyPressed(KeyCode::KeyLeftControl)) {
    m_camera->position -= (m_moveSpeed * deltaTime) * yAxis;
  }

  if (m_window.isMouseButtonPressed(ember::MouseButtonCode::MouseButtonRight)) {
    float xAngle = (mouseX - m_lastMouseX) * -m_turnSpeed * deltaTime;
    float yAngle = (mouseY - m_lastMouseY) * m_turnSpeed * deltaTime;

    auto q1 = glm::angleAxis(xAngle, yAxis);
    auto q2 = glm::angleAxis(yAngle, xAxis);
    m_camera->rotation = q2 * m_camera->rotation * q1;
  }

  m_lastMouseX = mouseX;
  m_lastMouseY = mouseY;
}
