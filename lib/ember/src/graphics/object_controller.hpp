#ifndef OBJECT_CONTROLLER_HPP
#define OBJECT_CONTROLLER_HPP

#include "../core/transform.hpp"
#include "../core/window.hpp"

namespace ember {

class ObjectController {
 public:
  ObjectController(Transform *transform, Window &window);

  auto update(float deltaTime) -> void;
  inline auto bindTransform(Transform *transform) -> void { m_transform = transform; }

 private:
  Transform *m_transform;
  Window &m_window;

  float m_moveSensitivity;
  float m_rotateSensitivity;
  float m_scaleSensitivity;
};

}  // namespace ember

#endif  // OBJECT_CONTROLLER_HPP