#ifndef OBJECT_3D_HPP
#define OBJECT_3D_HPP

#include <glm/glm.hpp>
#include "glm/gtc/quaternion.hpp"
#include "node.hpp"

namespace ember {

class Object3d : public Node {
 public:
  Object3d();
  virtual ~Object3d() = default;

  [[nodiscard]] auto getMatrix() const -> glm::mat4;
  [[nodiscard]] auto getInverse() const -> glm::mat4;

  auto setPosition(const glm::vec3 &position) -> void;

  auto setPosX(float x) -> void;
  auto setPosY(float y) -> void;
  auto setPosZ(float z) -> void;

  auto move(const glm::vec3 &move) -> void;

  auto setScale(const glm::vec3 &scale) -> void;
  auto scale(float factor) -> void;

  auto setRotation(const glm::quat &rotation) -> void;

  auto rotate(const glm::quat &rot) -> void;

  [[nodiscard]] inline auto getPosition() const { return m_position; }
  [[nodiscard]] inline auto getScale() const { return m_scale; }
  [[nodiscard]] inline auto getRotation() const { return m_rotation; }

 private:
  auto m_updateMatrices() const -> void;

  mutable bool m_dirty;
  glm::vec3 m_position;
  glm::vec3 m_scale;
  glm::quat m_rotation;
  mutable glm::mat4 m_mat;
  mutable glm::mat4 m_inv;
};

}  // namespace ember

#endif  // OBJECT_3D_HPP