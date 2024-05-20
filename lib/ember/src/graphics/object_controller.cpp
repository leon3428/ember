#include "object_controller.hpp"

#include <glm/gtc/matrix_transform.hpp>

ember::ObjectController::ObjectController(Transform *transform, Window &window)
    : m_transform(transform),
      m_window(window),
      m_moveSensitivity(0.01),
      m_rotateSensitivity(0.001),
      m_scaleSensitivity(0.001) {}

auto ember::ObjectController::update(float deltaTime) -> void {
  if (m_window.isKeyPressed(KeyCode::KeyKpEnter)) {
    // rotate
    if (m_window.isKeyPressed(KeyCode::KeyKp8)) {
      m_transform->rotation = glm::rotate(m_transform->rotation, m_rotateSensitivity * deltaTime, {1.0f, 0.0f, 0.0f});
    }
    if (m_window.isKeyPressed(KeyCode::KeyKp2)) {
      m_transform->rotation = glm::rotate(m_transform->rotation, -m_rotateSensitivity * deltaTime, {1.0f, 0.0f, 0.0f});
    }
    if (m_window.isKeyPressed(KeyCode::KeyKp4)) {
      m_transform->rotation = glm::rotate(m_transform->rotation, m_rotateSensitivity * deltaTime, {0.0f, 1.0f, 0.0f});
    }
    if (m_window.isKeyPressed(KeyCode::KeyKp6)) {
      m_transform->rotation = glm::rotate(m_transform->rotation, -m_rotateSensitivity * deltaTime, {0.0f, 1.0f, 0.0f});
    }
    if (m_window.isKeyPressed(KeyCode::KeyKp1)) {
      m_transform->rotation = glm::rotate(m_transform->rotation, m_rotateSensitivity * deltaTime, {0.0f, 0.0f, 1.0f});
    }
    if (m_window.isKeyPressed(KeyCode::KeyKp7)) {
      m_transform->rotation = glm::rotate(m_transform->rotation, -m_rotateSensitivity * deltaTime, {0.0f, 0.0f, 1.0f});
    }

  } else {
    // translate
    if (m_window.isKeyPressed(KeyCode::KeyKp8)) {
      m_transform->position.z -= m_moveSensitivity * deltaTime;
    }
    if (m_window.isKeyPressed(KeyCode::KeyKp2)) {
      m_transform->position.z += m_moveSensitivity * deltaTime;
    }
    if (m_window.isKeyPressed(KeyCode::KeyKp4)) {
      m_transform->position.x -= m_moveSensitivity * deltaTime;
    }
    if (m_window.isKeyPressed(KeyCode::KeyKp6)) {
      m_transform->position.x += m_moveSensitivity * deltaTime;
    }
    if (m_window.isKeyPressed(KeyCode::KeyKp1)) {
      m_transform->position.y -= m_moveSensitivity * deltaTime;
    }
    if (m_window.isKeyPressed(KeyCode::KeyKp7)) {
      m_transform->position.y += m_moveSensitivity * deltaTime;
    }
    if (m_window.isKeyPressed(KeyCode::KeyKpSubtract)) {
      m_transform->scale -= m_scaleSensitivity * deltaTime;
    }
    if (m_window.isKeyPressed(KeyCode::KeyKpAdd)) {
      m_transform->scale += m_scaleSensitivity * deltaTime;
    }
  }
}
