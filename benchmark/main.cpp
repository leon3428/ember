#include <format>
#include <iostream>

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ember.hpp"
#include "glm/fwd.hpp"

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
    renderEngine.setCamera(&camera);

    auto scene = ember::Node();

    auto pLight = scene.emplaceChild<ember::Light>();
    pLight->ambientIntensity = {0.3f, 0.3f, 0.3f, 1.0f};
    pLight->diffuseIntensity = {1.5f, 1.5f, 1.5f, 1.0f};
    pLight->specularIntensity = {1.5f, 1.5f, 1.5f, 1.0f};
    pLight->position.y = -8;
    pLight->position.z = 5;

    auto headNode = ember::loadObject("robotScene"_id);
    scene.steal(headNode);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    auto startTime = std::chrono::high_resolution_clock::now();

    ember::Circle cameraCurve(40.0f);
    glm::vec3 origin = {0.0f, 0.0f, 0.0f};
    int numFrames = 100;

    for (int i = 0; i < numFrames && !window.shouldClose(); i++) {
      auto pos = cameraCurve.getPosition(static_cast<float>(i) / static_cast<float>(numFrames - 1));
      camera.position.x = pos(0);
      camera.position.y = -20;
      camera.position.z = pos(2);
      camera.lookAt(origin);

      renderEngine.render(&scene);
      window.update();
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() / 1000.0f;
    auto avgFrameTime = deltaTime / static_cast<float>(numFrames);
    std::cout << std::format("Average FPS: {:.2f}, Average Frame Time: {:.2f}ms\n", 1000.0f / avgFrameTime,
                             avgFrameTime);

    resourceManager->clear();
  }

  glfwTerminate();
  return 0;
}