#include <array>
#include <chrono>
#include <iostream>
#include <vector>

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
    auto &eventBus = window.getEventBus();

    ember::PerspectiveCamera camera(glm::radians(45.0f), 0.1f, 100.0f);
    camera.pos.z = 5;
    renderEngine.pActiveCamera = &camera;

    ember::FpsCameraController cameraController(camera, window);

    auto vendor = glGetString(GL_VENDOR);
    auto renderer = glGetString(GL_RENDERER);
    std::cout << vendor << '\n' << renderer << '\n';

    std::vector<ember::RenderGroup> renderGroups;
    std::vector<ember::Transform> transforms;

    auto mesh = resourceManager.getStaticMesh("head"_id);
    ember::SolidColorMaterial material1;
    renderGroups.emplace_back(&material1, mesh, mesh->getNumVertices(), 0);
    transforms.emplace_back();
    transforms[0].position.y = 3;

    ember::SolidColorMaterial material2;
    material2.color = {0.0f, 1.0f, 1.0f, 1.0f};
    renderGroups.emplace_back(&material2, mesh, mesh->getNumVertices(), 0);
    transforms.emplace_back();
    transforms[1].position.x = 4;
    transforms[1].rotation = glm::rotate(transforms[1].rotation, glm::radians(45.0f), {0.0, 1.0, 0.0});

    ember::ObjectController objectController(&transforms[0], window);
    size_t activeObject = 0;

    eventBus.subscribe<ember::KeyPressedEvent>(
        [&activeObject, &transforms, &objectController](const ember::KeyPressedEvent &e) {
          if (e.keyCode == ember::KeyCode::KeyLeft) {
            activeObject++;
            if (activeObject >= transforms.size()) activeObject = 0;
            objectController.bindTransform(&transforms[activeObject]);
          }
          if (e.keyCode == ember::KeyCode::KeyRight) {
            if (activeObject == 0)
              activeObject = transforms.size() - 1;
            else
              activeObject--;
            objectController.bindTransform(&transforms[activeObject]);
          }
          std::cout << activeObject << '\n';
        });

    renderEngine.wireframeMode();
    renderEngine.drawAxis();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    auto prevTime = std::chrono::high_resolution_clock::now();

    while (!window.shouldClose()) {
      auto time = std::chrono::high_resolution_clock::now();
      auto deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(time - prevTime).count() / 1000.0f;
      prevTime = time;

      objectController.update(deltaTime);
      cameraController.update(deltaTime);
      renderEngine.render(renderGroups, transforms);

      window.update();
    }

    resourceManager.clear();
  }
  glfwTerminate();

  return 0;
}