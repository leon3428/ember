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
    resourceMap.addNamedResource("head"_id, "./assets/glava.obj");

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

    auto mesh = resourceManager.getStaticMesh("head"_id);
    ember::SolidColorMaterial material1;
    ember::RenderGroup renderGroup1 = {&material1, mesh, mesh->getNumVertices(), 0};
    ember::Transform transform1;

    ember::SolidColorMaterial material2;
    material2.color = {0.0f, 1.0f, 1.0f, 1.0f};
    ember::RenderGroup renderGroup2 = {&material2, mesh, mesh->getNumVertices(), 0};
    ember::Transform transform2;
    transform2.position.x = 4;
    transform2.rotation = glm::rotate(transform2.rotation, glm::radians(45.0f), {0.0, 1.0, 0.0});

    renderEngine.wireframeMode();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    auto prevTime = std::chrono::high_resolution_clock::now();

    while (!window.shouldClose()) {
      auto time = std::chrono::high_resolution_clock::now();

      auto deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(time - prevTime).count() / 1000.0f;

      prevTime = time;

      glClear(GL_COLOR_BUFFER_BIT);

      cameraController.update(deltaTime);

      renderEngine.queue(renderGroup1, transform1);
      renderEngine.queue(renderGroup2, transform2);

      window.update();
    }

    resourceManager.clear();
  }
  glfwTerminate();

  return 0;
}