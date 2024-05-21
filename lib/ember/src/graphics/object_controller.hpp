#ifndef OBJECT_CONTROLLER_HPP
#define OBJECT_CONTROLLER_HPP

#include "../core/window.hpp"
#include "object3d.hpp"

namespace ember {

class ObjectController {
 public:
  ObjectController(Object3d *pObject, Window &window);

  auto update(float deltaTime) -> void;
  inline auto bindTransform(Object3d *pObject) -> void { m_pObject = pObject; }

 private:
  Object3d *m_pObject;
  Window &m_window;

  float m_moveSensitivity;
  float m_rotateSensitivity;
  float m_scaleSensitivity;
};

}  // namespace ember

#endif  // OBJECT_CONTROLLER_HPP