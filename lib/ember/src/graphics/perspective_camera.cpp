#include "perspective_camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

ember::PerspectiveCamera::PerspectiveCamera(float fov, float nearPlane, float farPlane)
    : pos(0.0f, 0.0f, 0.0f),
      up(0.0f, 1.0f, 0.0f),
      direction(0.0f, 0.0f, -1.0f),
      m_fov(fov),
      m_nearPlane(nearPlane),
      m_farPlane(farPlane) {}

auto ember::PerspectiveCamera::getProjectionMatrix(int width, int height) const -> glm::mat4 {
  return glm::perspective(m_fov, static_cast<float>(width) / static_cast<float>(height), m_nearPlane, m_farPlane);
}

auto ember::PerspectiveCamera::getViewMatrix() const -> glm::mat4 { return glm::lookAt(pos, pos + direction, up); }
