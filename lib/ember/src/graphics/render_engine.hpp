#ifndef RENDER_ENGINE_HPP
#define RENDER_ENGINE_HPP

#include <glad/glad.h>
#include <cstdint>
#include <memory>
#include <vector>
#include "../core/window.hpp"
#include "camera.hpp"
#include "node.hpp"
#include "renderable.hpp"
#include "uniform_buffer.hpp"

namespace ember {

struct LightData {
  glm::vec4 ambientIntensity;
  glm::vec4 diffuseIntensity;
  glm::vec4 specularIntensity;
  glm::vec4 position;
};

class RenderCommand {
 public:
  RenderCommand(const Renderable *pRenderable);

  [[nodiscard]] inline auto getRenderable() const { return m_pRenderable; }
  auto getProgram() const -> uint32_t;

  auto operator<=>(const RenderCommand &) const = default;

 private:
  uint32_t m_cmd;
  const Renderable *m_pRenderable;
};

class RenderEngine {
 public:
  RenderEngine(Window &window);

  auto render(const Node *pScene) -> void;

  inline auto setCamera(Camera *pCamera) { m_pCamera = pCamera; }

 private:
  auto m_populateQueue(const Node *pNode) -> void;

  Window &m_window;
  Camera *m_pCamera;

  LightData m_lightData;
  std::unique_ptr<UniformBuffer> m_pLightUniformBuffer;

  std::vector<RenderCommand> m_renderQueue;
};
}  // namespace ember

#endif  // RENDER_ENGINE_HPP