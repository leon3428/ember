#ifndef RENDER_ENGINE_HPP
#define RENDER_ENGINE_HPP

#include <glad/glad.h>
#include "../core/transform.hpp"
#include "../core/window.hpp"
#include "camera.hpp"
#include "render_group.hpp"

namespace ember {

class RenderEngine {
 public:
  RenderEngine(Window &window);

  void queue(const RenderGroup &renderGroup, const Transform &transform);
  auto wireframeMode() -> void;

  // TODO: remove this
  ICamera *pActiveCamera;
  Transform *pActiveCameraTransform;

 private:
  Window &m_window;
};
}  // namespace ember

#endif  // RENDER_ENGINE_HPP