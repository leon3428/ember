#include "render_engine.hpp"

#include <glad/glad.h>
#include <iostream>
#include "axis_mesh.hpp"

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
}

auto ember::RenderEngine::frameStart() -> void {
  glClear(GL_COLOR_BUFFER_BIT);

  if (m_drawAxis) {
    auto axisRenderGroup = getAxisRenderGroup();

    axisRenderGroup.pMaterial->bindProgram();
    axisRenderGroup.pMesh->bind();

    auto [width, height] = m_window.getSize();
    auto mvp = pActiveCamera->getProjectionMatrix(width, height) * pActiveCamera->getViewMatrix();
    axisRenderGroup.pMaterial->uploadMvp(mvp);

    glDrawElements(GL_LINES, axisRenderGroup.vertexCnt, GL_UNSIGNED_INT,
                   reinterpret_cast<void *>(axisRenderGroup.byteOffset));
  }
}

void ember::RenderEngine::queue(const RenderGroup &renderGroup, const Transform &transform) {
  renderGroup.pMaterial->bindProgram();
  renderGroup.pMesh->bind();
  renderGroup.pMaterial->uploadUniforms();

  auto [width, height] = m_window.getSize();
  auto mvp = pActiveCamera->getProjectionMatrix(width, height) * pActiveCamera->getViewMatrix() * transform.getMatrix();
  renderGroup.pMaterial->uploadMvp(mvp);

  glDrawElements(GL_TRIANGLES, renderGroup.vertexCnt, GL_UNSIGNED_INT,
                 reinterpret_cast<void *>(renderGroup.byteOffset));

  if (m_drawAxis) {
    auto axisRenderGroup = getAxisRenderGroup();

    axisRenderGroup.pMaterial->bindProgram();
    axisRenderGroup.pMesh->bind();
    axisRenderGroup.pMaterial->uploadMvp(mvp);

    glDrawElements(GL_LINES, axisRenderGroup.vertexCnt, GL_UNSIGNED_INT,
                   reinterpret_cast<void *>(axisRenderGroup.byteOffset));
  }
}

auto ember::RenderEngine::wireframeMode() -> void { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }
