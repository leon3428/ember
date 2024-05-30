#include "object_controller.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include "glm/ext/quaternion_trigonometric.hpp"
#include "glm/fwd.hpp"

ember::ObjectController::ObjectController(Object3d *pObject, Window &window)
    : m_pObject(pObject),
      m_window(window),
      m_moveSensitivity(0.01),
      m_rotateSensitivity(0.001),
      m_scaleSensitivity(0.001) {}

auto ember::ObjectController::update(float deltaTime) -> void {
  if (m_window.isKeyPressed(KeyCode::KeyKpEnter)) {
    // rotate
    glm::quat rot = m_pObject->getRotation();

    if (m_window.isKeyPressed(KeyCode::KeyKp8)) {
      auto q = glm::angleAxis(m_rotateSensitivity * deltaTime, xAxis);
      rot *= q;
    }
    if (m_window.isKeyPressed(KeyCode::KeyKp2)) {
      auto q = glm::angleAxis(-m_rotateSensitivity * deltaTime, xAxis);
      rot *= q;
    }
    if (m_window.isKeyPressed(KeyCode::KeyKp4)) {
      auto q = glm::angleAxis(m_rotateSensitivity * deltaTime, yAxis);
      rot *= q;
    }
    if (m_window.isKeyPressed(KeyCode::KeyKp6)) {
      auto q = glm::angleAxis(-m_rotateSensitivity * deltaTime, yAxis);
      rot *= q;
    }
    if (m_window.isKeyPressed(KeyCode::KeyKp1)) {
      auto q = glm::angleAxis(m_rotateSensitivity * deltaTime, zAxis);
      rot *= q;
    }
    if (m_window.isKeyPressed(KeyCode::KeyKp7)) {
      auto q = glm::angleAxis(-m_rotateSensitivity * deltaTime, zAxis);
      rot *= q;
    }

    m_pObject->setRotation(rot);

  } else {
    // translate
    glm::vec3 move(0.0f);
    float scaleFactor = 1.0f;

    if (m_window.isKeyPressed(KeyCode::KeyKp2)) {
      move.z -= m_moveSensitivity * deltaTime;
    }
    if (m_window.isKeyPressed(KeyCode::KeyKp8)) {
      move.z += m_moveSensitivity * deltaTime;
    }
    if (m_window.isKeyPressed(KeyCode::KeyKp4)) {
      move.x -= m_moveSensitivity * deltaTime;
    }
    if (m_window.isKeyPressed(KeyCode::KeyKp6)) {
      move.x += m_moveSensitivity * deltaTime;
    }
    if (m_window.isKeyPressed(KeyCode::KeyKp1)) {
      move.y -= m_moveSensitivity * deltaTime;
    }
    if (m_window.isKeyPressed(KeyCode::KeyKp7)) {
      move.y += m_moveSensitivity * deltaTime;
    }
    if (m_window.isKeyPressed(KeyCode::KeyKpSubtract)) {
      scaleFactor -= m_scaleSensitivity * deltaTime;
    }
    if (m_window.isKeyPressed(KeyCode::KeyKpAdd)) {
      scaleFactor += m_scaleSensitivity * deltaTime;
    }

    m_pObject->move(move);
    m_pObject->scale(scaleFactor);
  }
}
