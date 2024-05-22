#ifndef RENDER_ENGINE_HPP
#define RENDER_ENGINE_HPP

#include <glad/glad.h>
#include <memory>
#include "../core/window.hpp"
#include "camera.hpp"
#include "node.hpp"
#include "uniform_buffer.hpp"

namespace ember {

struct LightData {
  glm::vec4 ambientIntensity;
  glm::vec4 diffuseIntensity;
  glm::vec4 specularIntensity;
  glm::vec4 position;
};

class RenderEngine {
 public:
  RenderEngine(Window &window);

  auto render(const Node *pScene) -> void;
  auto wireframeMode() -> void;

  inline auto drawAxis() -> void { m_drawAxis = true; }
  inline auto setCamera(Camera *pCamera) { m_pCamera = pCamera; }
  inline auto setDebugMode(bool debug) { m_debugMode = debug; }

 private:
  auto m_renderHelper(const Node *pNode) -> void;

  Window &m_window;
  Camera *m_pCamera;
  bool m_drawAxis;
  bool m_debugMode;

  LightData m_lightData;
  std::unique_ptr<UniformBuffer> m_pLightUniformBuffer;
};
}  // namespace ember

#endif  // RENDER_ENGINE_HPP