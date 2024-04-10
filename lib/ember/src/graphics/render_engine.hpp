#ifndef RENDER_ENGINE_HPP
#define RENDER_ENGINE_HPP

#include <glad/glad.h>
#include <vector>
#include "../core/transform.hpp"
#include "../core/window.hpp"
#include "camera.hpp"
#include "render_group.hpp"

namespace ember {

class RenderEngine {
 public:
  RenderEngine(Window &window);

  auto render(const std::vector<RenderGroup> &renderGroups, const std::vector<Transform> &transforms) -> void;
  auto wireframeMode() -> void;

  inline auto drawAxis() -> void { m_drawAxis = true; }

  // TODO: remove this
  ICamera *pActiveCamera;

 private:
  Window &m_window;
  bool m_drawAxis;
};
}  // namespace ember

#endif  // RENDER_ENGINE_HPP