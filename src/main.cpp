#include <iostream>
#include <memory>
#include <vector>

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ember.hpp"

int main(int, char *argv[]) {
  std::cout << argv[0] << ' ' << argv[1] << std::endl;

  ember::project::load(argv[1]);

  {
    auto resourceManager = ember::getResourceManager();

    auto width = 800;
    auto height = 600;
    ember::Window window("Ember", width, height);
    ember::RenderEngine renderEngine(window);

    ember::PerspectiveCamera camera(glm::radians(45.0f), 0.1f, 100.0f);
    ember::FpsCameraController cameraController(&camera, window);
    camera.position.z = -10;
    renderEngine.pActiveCamera = &camera;

    auto scene = ember::Node();
    scene.children.push_back(std::make_unique<ember::Renderable>());

    auto pHead = static_cast<ember::Renderable *>(scene.children[0].get());

    ember::SolidColorMaterial material1;
    pHead->pMaterial = &material1;
    auto mesh = resourceManager->getMesh("headMesh"_id);
    pHead->pMesh = mesh;
    pHead->vertexCnt = mesh->getNumVertices();
    pHead->byteOffset = 0;
    pHead->position.y = 1;

    renderEngine.wireframeMode();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    auto prevTime = std::chrono::high_resolution_clock::now();

    while (!window.shouldClose()) {
      auto time = std::chrono::high_resolution_clock::now();
      auto deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(time - prevTime).count() / 1000.0f;
      prevTime = time;

      cameraController.update(deltaTime);
      renderEngine.render(&scene);

      window.update();
    }

    resourceManager->clear();
  }

  glfwTerminate();
  return 0;
}