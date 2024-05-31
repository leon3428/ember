#ifndef RENDER_ENGINE_HPP
#define RENDER_ENGINE_HPP

#include <glad/glad.h>
#include <cstdint>
#include <vector>
#include "../core/window.hpp"
#include "camera.hpp"
#include "node.hpp"
#include "renderable.hpp"
#include "shadow_map_material.hpp"
#include "texture.hpp"
#include "uniform_buffer.hpp"
#include "light.hpp"

namespace ember {

struct LightData {
  glm::vec4 ambientIntensity;
  glm::vec4 diffuseIntensity;
  glm::vec4 specularIntensity;
  glm::vec4 position;
};

struct SceneData {
  glm::mat4 camera_pv;
  glm::mat4 light_pv;
  glm::vec4 viewPos;
  LightData lightData;
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
  auto m_shadowPass() -> void;
  auto m_finalPass() -> void;
  auto m_uploadSceneData() -> void;

  Window &m_window;
  Camera *m_pCamera;

  SceneData m_sceneData;
  UniformBuffer m_SceneDataUniformBuffer;

  std::vector<RenderCommand> m_renderQueue;
  std::vector<const Light *> m_lights;

  ShadowMapMaterial m_shadowMapMaterial;
  Texture m_shadowMap;
  uint32_t m_shadowMapFBO;
};
}  // namespace ember

#endif  // RENDER_ENGINE_HPP