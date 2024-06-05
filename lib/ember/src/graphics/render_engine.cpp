#include "render_engine.hpp"

#include <GL/gl.h>
#include <GL/glext.h>
#include <glad/glad.h>
#include <algorithm>
#include <array>
#include <iostream>
#include <limits>
#include <stdexcept>
#include "../config.hpp"
#include "../resource_manager/resource_manager.hpp"
#include "glm/ext/quaternion_common.hpp"
#include "glm/trigonometric.hpp"
#include "light.hpp"
#include "node.hpp"
#include "renderable.hpp"
#include "stbimage/stb_image_write.hpp"
#include "texture.hpp"
#include "uniform_buffer.hpp"

#ifdef NDEBUG

void glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei, const char *message,
                   const void *) {
  // ignore non-significant error/warning codes
  if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

  std::cout << "---------------" << std::endl;
  std::cout << "Debug message (" << id << "): " << message << std::endl;

  switch (source) {
    case GL_DEBUG_SOURCE_API:
      std::cout << "Source: API";
      break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
      std::cout << "Source: Window System";
      break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
      std::cout << "Source: Shader Compiler";
      break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:
      std::cout << "Source: Third Party";
      break;
    case GL_DEBUG_SOURCE_APPLICATION:
      std::cout << "Source: Application";
      break;
    case GL_DEBUG_SOURCE_OTHER:
      std::cout << "Source: Other";
      break;
  }
  std::cout << std::endl;

  switch (type) {
    case GL_DEBUG_TYPE_ERROR:
      std::cout << "Type: Error";
      break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
      std::cout << "Type: Deprecated Behaviour";
      break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
      std::cout << "Type: Undefined Behaviour";
      break;
    case GL_DEBUG_TYPE_PORTABILITY:
      std::cout << "Type: Portability";
      break;
    case GL_DEBUG_TYPE_PERFORMANCE:
      std::cout << "Type: Performance";
      break;
    case GL_DEBUG_TYPE_MARKER:
      std::cout << "Type: Marker";
      break;
    case GL_DEBUG_TYPE_PUSH_GROUP:
      std::cout << "Type: Push Group";
      break;
    case GL_DEBUG_TYPE_POP_GROUP:
      std::cout << "Type: Pop Group";
      break;
    case GL_DEBUG_TYPE_OTHER:
      std::cout << "Type: Other";
      break;
  }
  std::cout << std::endl;

  switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH:
      std::cout << "Severity: high";
      break;
    case GL_DEBUG_SEVERITY_MEDIUM:
      std::cout << "Severity: medium";
      break;
    case GL_DEBUG_SEVERITY_LOW:
      std::cout << "Severity: low";
      break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
      std::cout << "Severity: notification";
      break;
  }
  std::cout << std::endl;
  std::cout << std::endl;
}

#endif

ember::RenderCommand::RenderCommand(const Renderable *pRenderable) : m_cmd(0), m_pRenderable(pRenderable) {
  m_cmd = pRenderable->pMaterial->getEmberId();
}

auto ember::RenderCommand::getProgram() const -> uint32_t { return m_cmd; }

ember::RenderEngine::RenderEngine(Window &window)
    : m_window(window),
      m_SceneDataUniformBuffer(&m_sceneData, 2, GL_DYNAMIC_DRAW),
      m_shadowMap({config::shadowMapSize, config::shadowMapSize, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_FLOAT,
                   GL_NEAREST, GL_NEAREST, false},
                  NULL) {
#ifdef NDEBUG
  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageCallback(glDebugOutput, nullptr);
  glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
#endif
  std::array<PosColVertex, 6> axisVertices = {ember::PosColVertex({0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}),
                                              ember::PosColVertex({1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}),
                                              ember::PosColVertex({0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}),
                                              ember::PosColVertex({0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}),
                                              ember::PosColVertex({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}),
                                              ember::PosColVertex({0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f})};

  std::array<uint32_t, 6> axisIndices = {0, 1, 2, 3, 4, 5};
  Mesh mesh(std::span<const PosColVertex>{axisVertices}, axisIndices);

  getResourceManager()->moveMesh("axisMesh"_id, std::move(mesh));

  constexpr int size = 8;
  std::array<unsigned char, size * size * 3> emptyTextureData;
  for (auto &v : emptyTextureData) v = 255;
  Texture emptyTexture({size, size, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, true},
                       emptyTextureData.data());
  getResourceManager()->moveTexture("EmberEmptyTexture"_id, std::move(emptyTexture));

  std::array<unsigned char, size * size * 3> emptyNormalMapData;
  for (size_t i = 0; i < size * size * 3; i += 3) {
    emptyNormalMapData[i] = 128;
    emptyNormalMapData[i + 1] = 128;
    emptyNormalMapData[i + 2] = 255;
  }
  Texture emptyNormalMap({size, size, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, true},
                       emptyNormalMapData.data());
  getResourceManager()->moveTexture("EmberEmptyNormalMap"_id, std::move(emptyNormalMap));

  glEnable(GL_MULTISAMPLE);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glEnable(GL_DEPTH_TEST);

  glGenFramebuffers(1, &m_shadowMapFBO);
  glBindFramebuffer(GL_FRAMEBUFFER, m_shadowMapFBO);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_shadowMap.getTextureId(), 0);
  glDrawBuffer(GL_NONE);
  glReadBuffer(GL_NONE);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

auto ember::RenderEngine::render(const Node *pScene) -> void {
  if (!pScene->getChild(0)->is(NodeAttribute::Light)) throw std::runtime_error("Light not found");

  m_renderQueue.clear();
  m_lights.clear();
  m_populateQueue(pScene);
  std::sort(m_renderQueue.begin(), m_renderQueue.end());

  m_uploadSceneData();

  m_shadowPass();
  m_finalPass();
}

auto ember::RenderEngine::m_populateQueue(const Node *pNode) -> void {
  if (pNode->is(NodeAttribute::Light)) {
    auto pLight = static_cast<const Light *>(pNode);
    m_lights.push_back(pLight);

  } else if (pNode->is(NodeAttribute::Renderable)) {
    auto pRenderable = static_cast<const Renderable *>(pNode);
    m_renderQueue.emplace_back(pRenderable);
  }

  for (auto pChild : *pNode) {
    m_populateQueue(pChild);
  }
}

auto ember::RenderEngine::m_shadowPass() -> void {
  glViewport(0, 0, config::shadowMapSize, config::shadowMapSize);
  glBindFramebuffer(GL_FRAMEBUFFER, m_shadowMapFBO);
  glClear(GL_DEPTH_BUFFER_BIT);

  m_shadowMapMaterial.bindProgram();

  // render
  for (auto &cmd : m_renderQueue) {
    auto pRenderable = cmd.getRenderable();

    m_shadowMapMaterial.uploadUniforms(pRenderable->getMatrix(), pRenderable->getInverse());
    pRenderable->pVertexArray->bind();

    if (pRenderable->pVertexArray->isIndexed()) {
      glDrawElements(pRenderable->pVertexArray->getPrimitiveType(), pRenderable->vertexCnt, GL_UNSIGNED_INT,
                     reinterpret_cast<void *>(pRenderable->byteOffset));
    } else {
      glDrawArrays(pRenderable->pVertexArray->getPrimitiveType(), 0, pRenderable->vertexCnt);
    }
  }

  m_shadowMapMaterial.unbindProgram();
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

auto ember::RenderEngine::m_finalPass() -> void {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  auto [width, height] = m_window.getSize();
  glViewport(0, 0, width, height);

  uint32_t lastShaderProgram = std::numeric_limits<uint32_t>::max();

  for (auto &cmd : m_renderQueue) {
    auto pRenderable = cmd.getRenderable();
    if (cmd.getProgram() != lastShaderProgram) {
      lastShaderProgram = cmd.getProgram();
      pRenderable->pMaterial->bindProgram();
    }

    pRenderable->pMaterial->uploadUniforms(pRenderable->getMatrix(), pRenderable->getInverse());
    glActiveTexture(GL_TEXTURE0);
    m_shadowMap.bind();
    pRenderable->pVertexArray->bind();

    if (pRenderable->pVertexArray->isIndexed()) {
      glDrawElements(pRenderable->pVertexArray->getPrimitiveType(), pRenderable->vertexCnt, GL_UNSIGNED_INT,
                     reinterpret_cast<void *>(pRenderable->byteOffset));
    } else {
      glDrawArrays(pRenderable->pVertexArray->getPrimitiveType(), 0, pRenderable->vertexCnt);
    }
  }
}

auto ember::RenderEngine::m_uploadSceneData() -> void {
  // TODO: support multiple lights
  auto [width, height] = m_window.getSize();

  auto pLight = m_lights[0];
  auto p = glm::perspective(glm::radians(75.0f), 1.0f, 5.5f, 20.5f);
  m_sceneData.light_pv = p * pLight->getInverse();

  m_sceneData.lightData.ambientIntensity = pLight->ambientIntensity;
  m_sceneData.lightData.diffuseIntensity = pLight->diffuseIntensity;
  m_sceneData.lightData.specularIntensity = pLight->specularIntensity;
  m_sceneData.lightData.position = glm::vec4(pLight->getPosition(), 1.0f);

  auto viewMat = m_pCamera->getViewMatrix();
  auto projectionMat = m_pCamera->getProjectionMatrix(width, height);

  m_sceneData.camera_pv = projectionMat * viewMat;
  m_sceneData.viewPos = glm::vec4(m_pCamera->getPosition(), 1.0f);

  m_SceneDataUniformBuffer.bind();
  glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(SceneData), &m_sceneData);
  m_SceneDataUniformBuffer.unbind();
}