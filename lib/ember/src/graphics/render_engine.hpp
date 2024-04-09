#ifndef RENDER_ENGINE_HPP
#define RENDER_ENGINE_HPP

#include "render_group.hpp"
#include "../core/window.hpp"
#include "../core/transform.hpp"
#include "camera.hpp"

namespace ember {

class RenderEngine {
 public:
  RenderEngine(Window& window);

  void queue(const RenderGroup& renderGroup, const Transform& transform);

  // TODO: remove this
  ICamera *pActiveCamera;
  Transform *pActiveCameraTransform;

 private:
  Window &m_window;
};
}  // namespace ember

#endif  // RENDER_ENGINE_HPP