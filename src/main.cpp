#include <array>
#include <chrono>
#include <iostream>

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
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

    ember::Transform cameraTransform;
    cameraTransform.position.z = -5;
    ember::PerspectiveCamera camera(glm::radians(45.0f), 0.1f, 100.0f);
    renderEngine.pActiveCamera = &camera;
    renderEngine.pActiveCameraTransform = &cameraTransform;

    ember::FpsCameraController cameraController(window, cameraTransform);

    auto vendor = glGetString(GL_VENDOR);
    auto renderer = glGetString(GL_RENDERER);
    std::cout << vendor << '\n' << renderer << '\n';

    std::array<ember::PosVertex, 4> vertices = {
        ember::PosVertex{glm::vec3{0.5f, 0.5f, 0.0f}}, ember::PosVertex{glm::vec3{0.5f, -0.5f, 0.0f}},
        ember::PosVertex{glm::vec3{-0.5f, -0.5f, 0.0f}}, ember::PosVertex{glm::vec3{-0.5f, 0.5f, 0.0f}}};

    uint32_t indices[] = {
        // note that we start from 0!
        0, 1, 3,  // first triangle
        1, 2, 3   // second triangle
    };

    ember::StaticMesh mesh(std::span<ember::PosVertex>{vertices}, indices);
    ember::SolidColorMaterial material;

    ember::RenderGroup renderGroup = {&material, &mesh, mesh.getNumVertices(), 0};
    ember::Transform transform;
    transform.rotation = glm::rotate(transform.rotation, glm::radians(45.0f), {0.0, 1.0, 0.0});

    renderEngine.wireframeMode();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    auto prevTime = std::chrono::high_resolution_clock::now();

    while (!window.shouldClose()) {
      auto time = std::chrono::high_resolution_clock::now();

      auto deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(time - prevTime).count() / 1000.0f;

      prevTime = time;

      glClear(GL_COLOR_BUFFER_BIT);

      cameraController.update(deltaTime);

      renderEngine.queue(renderGroup, transform);

      window.update();
    }

    resourceManager.clear();
  }
  glfwTerminate();

  return 0;
}