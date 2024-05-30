#include "render_engine.hpp"

#include <glad/glad.h>
#include <iostream>
#include <memory>
#include <stdexcept>
#include "../resource_manager/resource_manager.hpp"
#include "light.hpp"
#include "node.hpp"
#include "renderable.hpp"
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

ember::RenderEngine::RenderEngine(Window &window) : m_window(window), m_drawAxis(false) {
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    throw std::runtime_error("Failed to initialize GLAD");
  }

  auto [width, height] = window.getSize();
  glViewport(0, 0, width, height);

#ifdef NDEBUG
  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageCallback(glDebugOutput, nullptr);
  glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
#endif

  auto &eventBus = window.getEventBus();
  eventBus.subscribe<ember::ResizeEvent>([](const ember::ResizeEvent &e) { glViewport(0, 0, e.width, e.height); });

  std::array<PosColVertex, 6> axisVertices = {ember::PosColVertex({0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}),
                                              ember::PosColVertex({1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}),
                                              ember::PosColVertex({0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}),
                                              ember::PosColVertex({0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}),
                                              ember::PosColVertex({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}),
                                              ember::PosColVertex({0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f})};

  std::array<uint32_t, 6> axisIndices = {0, 1, 2, 3, 4, 5};
  Mesh mesh(std::span<const PosColVertex>{axisVertices}, axisIndices);

  getResourceManager()->moveMesh("axisMesh"_id, std::move(mesh));

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glEnable(GL_DEPTH_TEST);

  m_pLightUniformBuffer = std::make_unique<UniformBuffer>(&m_lightData, 2, GL_DYNAMIC_DRAW );
}

auto ember::RenderEngine::render(const Node *pScene) -> void {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (!pScene->getChild(0)->is(NodeAttribute::Light)) throw std::runtime_error("Light not found");

  auto pLight = static_cast<const Light *>(pScene->getChild(0));
  m_lightData.ambientIntensity = pLight->ambientIntensity;
  m_lightData.diffuseIntensity = pLight->diffuseIntensity;
  m_lightData.specularIntensity = pLight->specularIntensity;
  m_lightData.position = m_pCamera->getViewMatrix() * glm::vec4(pLight->position, 1.0f);

  m_pLightUniformBuffer->bind();
  glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(LightData), &m_lightData);
  m_pLightUniformBuffer->unbind();

  m_renderHelper(pScene);
}

auto ember::RenderEngine::m_renderHelper(const Node *pNode) -> void {
  if (pNode->is(NodeAttribute::Light)) {
    // TODO: fix this

  } else if (pNode->is(NodeAttribute::Renderable)) {
    auto pRenderable = static_cast<const Renderable *>(pNode);

    pRenderable->pMaterial->bindProgram();
    pRenderable->pVertexArray->bind();
    pRenderable->pMaterial->uploadUniforms();

    auto [width, height] = m_window.getSize();
    pRenderable->pMaterial->uploadMvp(pRenderable->getMatrix(), m_pCamera->getViewMatrix(),
                                      m_pCamera->getProjectionMatrix(width, height));

    if (pRenderable->pVertexArray->isIndexed()) {
      glDrawElements(pRenderable->pVertexArray->getPrimitiveType(), pRenderable->vertexCnt, GL_UNSIGNED_INT,
                     reinterpret_cast<void *>(pRenderable->byteOffset));
    } else {
      glDrawArrays(pRenderable->pVertexArray->getPrimitiveType(), 0, pRenderable->vertexCnt);
    }
  }

  auto i = 0;
  for (auto pChild : *pNode) {
    std::cout << i++ << '\n';
    m_renderHelper(pChild);
  }
}

auto ember::RenderEngine::wireframeMode() -> void { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }
