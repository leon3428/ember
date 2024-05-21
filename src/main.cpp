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

    auto &eventBus = window.getEventBus();

    ember::PerspectiveCamera camera(glm::radians(45.0f), 0.1f, 100.0f);
    ember::FpsCameraController cameraController(&camera, window);
    camera.position.z = 10;
    renderEngine.setCamera(&camera);

    auto scene = ember::Node();
    scene.children.push_back(std::make_unique<ember::Renderable>());

    auto pHead = static_cast<ember::Renderable *>(scene.children[0].get());
    ember::ObjectController objController(pHead, window);

    ember::ProjectionSpaceCullingMaterial material1;
    pHead->pMaterial = &material1;
    auto mesh = resourceManager->getMesh("headMesh"_id);
    pHead->pVertexArray = mesh;
    pHead->vertexCnt = mesh->getNumVertices();
    pHead->byteOffset = 0;

    scene.children.push_back(std::make_unique<ember::Renderable>());
    auto pObj2 = static_cast<ember::Renderable *>(scene.children[1].get());

    ember::SceneSpaceCullingMaterial material2;
    material2.color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    pObj2->pMaterial = &material2;
    pObj2->pVertexArray = mesh;
    pObj2->vertexCnt = mesh->getNumVertices();
    pObj2->byteOffset = 0;
    pObj2->position.x = 2;

    scene.children.push_back(std::make_unique<ember::BezierCurve>(20));
    auto pBezierCurve = static_cast<ember::BezierCurve *>(scene.children[2].get());
    ember::Object3d *pBezierObject = pHead;

    eventBus.subscribe<ember::KeyPressedEvent>([pBezierCurve, pBezierObject](const ember::KeyPressedEvent &e) {
      if (e.keyCode == ember::KeyCode::KeyTab) {
        auto pos = pBezierObject->position;
        pos.x *= -1;
        pos.y *= -1;
        pBezierCurve->addPoint(pos, pBezierObject->rotation);
      }
    });

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    auto prevTime = std::chrono::high_resolution_clock::now();

    while (!window.shouldClose()) {
      auto time = std::chrono::high_resolution_clock::now();
      auto deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(time - prevTime).count() / 1000.0f;
      prevTime = time;

      objController.update(deltaTime);
      cameraController.update(deltaTime);
      renderEngine.render(&scene);

      window.update();
    }

    resourceManager->clear();
  }

  glfwTerminate();
  return 0;
}