#include <array>
#include <chrono>
#include <iostream>

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "ember.hpp"

int main(int, char *argv[]) {
  std::cout << argv[0] << std::endl;
  {
    auto &resourceManager = ember::getResourceManager();
    auto &resourceMap = resourceManager.getResourceMap();
    resourceMap.addNamedResource("shaderFolder"_id, "./shaders");

    auto width = 800;
    auto height = 600;
    ember::Window window("Ember", width, height);
    ember::RenderEngine renderEngine(window);
    // auto &eventBus = window.getEventBus();

    auto vendor = glGetString(GL_VENDOR);
    auto renderer = glGetString(GL_RENDERER);
    std::cout << vendor << '\n' << renderer << '\n';

    std::array<ember::PosVertex, 4> vertices = {
        ember::PosVertex{glm::vec3{0.9f, 0.9f, 0.0f}}, ember::PosVertex{glm::vec3{0.9f, 0.8f, 0.0f}},
        ember::PosVertex{glm::vec3{0.8f, 0.8f, 0.0f}}, ember::PosVertex{glm::vec3{0.8f, 0.9f, 0.0f}}};

    uint32_t indices[] = {
        // note that we start from 0!
        0, 1, 3,  // first triangle
        1, 2, 3   // second triangle
    };

    ember::StaticMesh mesh(std::span<ember::PosVertex>{vertices}, indices);
    ember::SolidColorMaterial material;

    ember::RenderGroup renderGroup = {&material, &mesh, mesh.getNumVertices(), 0};

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    while (!window.shouldClose()) {
      glClear(GL_COLOR_BUFFER_BIT);

      renderEngine.queue(renderGroup);

      window.update();
    }

    resourceManager.clear();
  }
  glfwTerminate();

  return 0;
}