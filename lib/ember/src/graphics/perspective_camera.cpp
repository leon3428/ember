#include "perspective_camera.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include "../core/my_glm.hpp"

ember::PerspectiveCamera::PerspectiveCamera(float fov, float nearPlane, float farPlane)
    : pos(0.0f, 0.0f, 0.0f),
      up(0.0f, 1.0f, 0.0f),
      direction(0.0f, 0.0f, -1.0f),
      m_fov(fov),
      m_nearPlane(nearPlane),
      m_farPlane(farPlane) {}

auto ember::PerspectiveCamera::getProjectionMatrix(int width, int height) const -> glm::mat4 {
  float top = m_nearPlane * tanf(0.5f * m_fov);
  float bottom = -top;
  float right = top * static_cast<float>(width) / static_cast<float>(height);
  float left = -right;

  return my_glm::frustum(left, right, bottom, top, m_nearPlane, m_farPlane);
}

auto ember::PerspectiveCamera::getViewMatrix() const -> glm::mat4 {
  return my_glm::lookAtMatrix(pos, pos + direction, up);
}
