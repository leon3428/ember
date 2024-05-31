#include "object3d.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/matrix.hpp"
#include "node.hpp"
#include "../core/utils.hpp"

ember::Object3d::Object3d()
    : m_dirty(false), m_position(0.0f), m_scale(1.0f), m_rotation(1.0f, 0.0f, 0.0f, 0.0f), m_mat(1.0f), m_inv(1.0f) {
  m_attributes |= static_cast<unsigned>(NodeAttribute::Object3d);
}

auto ember::Object3d::setPosition(const glm::vec3 &position) -> void {
  m_position = position;
  m_dirty = true;
}

auto ember::Object3d::setPosX(float x) -> void {
  m_position.x = x;
  m_dirty = true;
}
auto ember::Object3d::setPosY(float y) -> void {
  m_position.y = y;
  m_dirty = true;
}
auto ember::Object3d::setPosZ(float z) -> void {
  m_position.z = z;
  m_dirty = true;
}

auto ember::Object3d::move(const glm::vec3 &move) -> void {
  m_position += move;
  m_dirty = true;
}

auto ember::Object3d::setScale(const glm::vec3 &scale) -> void {
  m_scale = scale;
  m_dirty = true;
}

auto ember::Object3d::scale(float factor) -> void {
  m_scale *= factor;
  m_dirty = true;
}

auto ember::Object3d::setRotation(const glm::quat &rotation) -> void {
  m_rotation = rotation;
  m_dirty = true;
}

auto ember::Object3d::rotate(const glm::quat &rot) -> void {
  m_rotation *= rot;
  m_dirty = true;
}

auto ember::Object3d::lookAt(glm::vec3 target) -> void {
  auto dir = glm::normalize(target - getPosition());

  auto tmp = glm::quatLookAt(dir, yAxis);
  setRotation(tmp);
}

auto ember::Object3d::m_updateMatrices() const -> void {
  m_mat = glm::mat4(1.0f);
  m_mat = glm::translate(m_mat, m_position);
  m_mat *= glm::mat4_cast(m_rotation);
  m_mat = glm::scale(m_mat, m_scale);

  // if(m_scale.x == m_scale.y && m_scale.y == m_scale.z) {
  //   m_inv = glm::mat4(1.0f);
  //   m_inv = glm::scale(m_inv, 1.0f / m_scale);
  //   m_inv *= glm::transpose(glm::mat4_cast(m_rotation));
  //   m_inv = glm::translate(m_inv, -m_position);
  // } else {
  m_inv = glm::inverse(m_mat);
  // }
}

auto ember::Object3d::getMatrix() const -> glm::mat4 {
  if (m_dirty) {
    m_updateMatrices();
    m_dirty = false;
  }

  return m_mat;
}

auto ember::Object3d::getInverse() const -> glm::mat4 { 
  if (m_dirty) {
    m_updateMatrices();
    m_dirty = false;
  }

  return m_inv;
}
