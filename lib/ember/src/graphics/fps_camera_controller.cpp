#include "fps_camera_controller.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include "../core/utils.hpp"
#include "glm/ext/quaternion_trigonometric.hpp"
#include "glm/gtc/quaternion.hpp"

ember::FpsCameraController::FpsCameraController(Camera *camera, Window &window)
    : m_camera(camera), m_window(window), m_moveSpeed(0.01f), m_turnSpeed(0.0001f), m_lastMouseX(0), m_lastMouseY(0) {}

auto ember::FpsCameraController::update(float deltaTime) -> void {
  auto [mouseX, mouseY] = m_window.getMousePos();

  auto rotMat = glm::mat4_cast(m_camera->getRotation());
  auto right = glm::vec3(rotMat[0][0], rotMat[0][1], rotMat[0][2]);    // First row
  auto forward = glm::vec3(rotMat[2][0], rotMat[2][1], rotMat[2][2]);  // Third row
  glm::vec3 move(0.0f);

  if (m_window.isKeyPressed(KeyCode::KeyW)) {
    move -= (m_moveSpeed * deltaTime) * forward;
  }
  if (m_window.isKeyPressed(KeyCode::KeyS)) {
    move += (m_moveSpeed * deltaTime) * forward;
  }
  if (m_window.isKeyPressed(KeyCode::KeyA)) {
    move -= (m_moveSpeed * deltaTime) * right;
  }
  if (m_window.isKeyPressed(KeyCode::KeyD)) {
    move += (m_moveSpeed * deltaTime) * right;
  }
  if (m_window.isKeyPressed(KeyCode::KeyLeftControl)) {
    move -= (m_moveSpeed * deltaTime) * yAxis;
  }
  if (m_window.isKeyPressed(KeyCode::KeyLeftShift)) {
    move += (m_moveSpeed * deltaTime) * yAxis;
  }

  m_camera->move(move);

  if (m_window.isMouseButtonPressed(ember::MouseButtonCode::MouseButtonLeft)) {
    float xAngle = (mouseX - m_lastMouseX) * -m_turnSpeed * deltaTime;
    float yAngle = (mouseY - m_lastMouseY) * -m_turnSpeed * deltaTime;

    auto q1 = glm::angleAxis(xAngle, yAxis);
    auto q2 = glm::angleAxis(yAngle, xAxis);
    auto tmp = q1 * m_camera->getRotation() * q2;
    m_camera->setRotation(tmp);
  }

  m_lastMouseX = mouseX;
  m_lastMouseY = mouseY;
}
