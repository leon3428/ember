#include "object_controller.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include "glm/ext/quaternion_trigonometric.hpp"

ember::ObjectController::ObjectController(Object3d *pObject, Window &window)
    : m_pObject(pObject),
      m_window(window),
      m_moveSensitivity(0.01),
      m_rotateSensitivity(0.001),
      m_scaleSensitivity(0.001) {}

auto ember::ObjectController::update(float deltaTime) -> void {
  if (m_window.isKeyPressed(KeyCode::KeyKpEnter)) {
    // rotate
    if (m_window.isKeyPressed(KeyCode::KeyKp8)) {
      auto q = glm::angleAxis(m_rotateSensitivity * deltaTime, xAxis);
      m_pObject->rotation *= q;
    }
    if (m_window.isKeyPressed(KeyCode::KeyKp2)) {
      auto q = glm::angleAxis(-m_rotateSensitivity * deltaTime, xAxis);
      m_pObject->rotation *= q;
    }
    if (m_window.isKeyPressed(KeyCode::KeyKp4)) {
      auto q = glm::angleAxis(m_rotateSensitivity * deltaTime, yAxis);
      m_pObject->rotation *= q;
    }
    if (m_window.isKeyPressed(KeyCode::KeyKp6)) {
      auto q = glm::angleAxis(-m_rotateSensitivity * deltaTime, yAxis);
      m_pObject->rotation *= q;
    }
    if (m_window.isKeyPressed(KeyCode::KeyKp1)) {
      auto q = glm::angleAxis(m_rotateSensitivity * deltaTime, zAxis);
      m_pObject->rotation *= q;
    }
    if (m_window.isKeyPressed(KeyCode::KeyKp7)) {
      auto q = glm::angleAxis(-m_rotateSensitivity * deltaTime, zAxis);
      m_pObject->rotation *= q;
    }

  } else {
    // translate
    if (m_window.isKeyPressed(KeyCode::KeyKp2)) {
      m_pObject->position.z -= m_moveSensitivity * deltaTime;
    }
    if (m_window.isKeyPressed(KeyCode::KeyKp8)) {
      m_pObject->position.z += m_moveSensitivity * deltaTime;
    }
    if (m_window.isKeyPressed(KeyCode::KeyKp4)) {
      m_pObject->position.x -= m_moveSensitivity * deltaTime;
    }
    if (m_window.isKeyPressed(KeyCode::KeyKp6)) {
      m_pObject->position.x += m_moveSensitivity * deltaTime;
    }
    if (m_window.isKeyPressed(KeyCode::KeyKp7)) {
      m_pObject->position.y -= m_moveSensitivity * deltaTime;
    }
    if (m_window.isKeyPressed(KeyCode::KeyKp1)) {
      m_pObject->position.y += m_moveSensitivity * deltaTime;
    }
    if (m_window.isKeyPressed(KeyCode::KeyKpSubtract)) {
      m_pObject->scale -= m_scaleSensitivity * deltaTime;
    }
    if (m_window.isKeyPressed(KeyCode::KeyKpAdd)) {
      m_pObject->scale += m_scaleSensitivity * deltaTime;
    }
  }
}
