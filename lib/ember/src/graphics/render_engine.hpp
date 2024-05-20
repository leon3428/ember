#ifndef RENDER_ENGINE_HPP
#define RENDER_ENGINE_HPP

#include <glad/glad.h>
#include "../core/window.hpp"
#include "camera.hpp"
#include "node.hpp"

namespace ember {

class RenderEngine {
 public:
  RenderEngine(Window &window);

  auto render(const Node *pScene) -> void;
  auto wireframeMode() -> void;

  inline auto drawAxis() -> void { m_drawAxis = true; }

  // TODO: remove this
  ICamera *pActiveCamera;

 private:
  auto m_renderHelper(const Node *pNode) -> void;

  Window &m_window;
  bool m_drawAxis;
};
}  // namespace ember

#endif  // RENDER_ENGINE_HPP