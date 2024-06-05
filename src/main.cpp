#include <chrono>
#include <format>
#include <iostream>

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <thread>

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

    ember::PerspectiveCamera camera(glm::radians(45.0f), 0.1f, 200.0f);
    ember::FpsCameraController cameraController(&camera, window);
    camera.setPosZ(10);
    renderEngine.setCamera(&camera);

    auto scene = ember::Node();

    auto pLight = scene.emplaceChild<ember::Light>();
    pLight->ambientIntensity = {0.3f, 0.3f, 0.3f, 1.0f};
    pLight->diffuseIntensity = {1.5f, 1.5f, 1.5f, 1.0f};
    pLight->specularIntensity = {1.5f, 1.5f, 1.5f, 1.0f};
    pLight->setPosY(8);
    pLight->setPosZ(1);
    pLight->lookAt({0.0f, 0.0f, -5.0f});

    auto headNode = ember::loadObject("shadowMap2"_id);
    auto pCube = static_cast<ember::Renderable *>(headNode.getChild(0));
    scene.steal(headNode);

    ember::Circle cameraCurve(5.0f);
    scene.emplaceChild<ember::CurveNode>(&cameraCurve, 50);

    ember::ObjectController objController(pCube, window);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    auto prevTime = std::chrono::high_resolution_clock::now();

    while (!window.shouldClose()) {
      auto time = std::chrono::high_resolution_clock::now();
      auto deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(time - prevTime).count() / 1000.0f;
      if (deltaTime < 10) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10 - static_cast<int>(deltaTime)));
        time = std::chrono::high_resolution_clock::now();
        deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(time - prevTime).count() / 1000.0f;
      }

      prevTime = time;

      objController.update(deltaTime);
      cameraController.update(deltaTime);
      renderEngine.render(&scene);

      window.setTitle(std::format("FPS: {}, Frame Time: {}ms", 1000 / deltaTime, deltaTime));
      // auto pos = pLight ->getPosition();
      // std::cout << pos.x << ' ' << pos.y << ' ' << pos.z << '\n';

      window.update();
    }

    resourceManager->clear();
  }

  glfwTerminate();
  return 0;
}