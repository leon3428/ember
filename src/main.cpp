#include <array>
#include <cstddef>
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

    auto bezier1 = ember::Bezier();
    auto bezier2 = ember::Bezier();

    scene.children.push_back(std::make_unique<ember::BezierNode>(bezier1, 40));
    scene.children.push_back(std::make_unique<ember::BezierNode>(bezier2, 40));
    auto pBezierNode1 = static_cast<ember::BezierNode *>(scene.children[2].get());
    auto pBezierNode2 = static_cast<ember::BezierNode *>(scene.children[3].get());
    pBezierNode2->setColor({0.0f, 0.78f, 0.96f, 1.0f});
    ember::Object3d *pBezierObject = pHead;
    bool animationPlaying = false;
    float t = 0.0f;

    scene.children.push_back(std::make_unique<ember::Renderable>());
    auto pControlPoligon = static_cast<ember::Renderable *>(scene.children[4].get());
    ember::SolidColorMaterial material3;

    size_t vertexCnt = 0;
    std::array<ember::PosVertex, 20> controlPoligonVertices;
    ember::DynamicLineStrip<ember::PosVertex> controlPoligonStrip(controlPoligonVertices);

    material3.color = glm::vec4(0.7f, 0.7f, 0.7f, 1.0f);
    pControlPoligon->pMaterial = &material3;
    pControlPoligon->pVertexArray = &controlPoligonStrip;
    pControlPoligon->vertexCnt = 0;
    pControlPoligon->byteOffset = 0;

    std::vector<glm::quat> rotations;

    eventBus.subscribe<ember::KeyPressedEvent>([&bezier1, pBezierNode1, &bezier2, pBezierNode2, pBezierObject,
                                                &animationPlaying, &t, pControlPoligon, &controlPoligonStrip, &controlPoligonVertices, &vertexCnt, &rotations](const ember::KeyPressedEvent &e) {
      if (e.keyCode == ember::KeyCode::KeyTab) {
        auto pos = pBezierObject->position;
        pos.x *= -1;
        pos.y *= -1;
        bezier1.addInterpolatedPoint({pos.x, pos.y, pos.z});
        pBezierNode1->update();
        bezier2.addControlPoint({pos.x, pos.y, pos.z});
        pBezierNode2->update();

        controlPoligonVertices[vertexCnt] = {pos};
        vertexCnt++;
        controlPoligonStrip.writeVertices(0, controlPoligonVertices);
        pControlPoligon->vertexCnt=vertexCnt;

        rotations.push_back(pBezierObject->rotation);

      } else if (e.keyCode == ember::KeyCode::KeySpace) {
        animationPlaying = true;
        t = 0.0f;
      }
    });

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    auto prevTime = std::chrono::high_resolution_clock::now();

    while (!window.shouldClose()) {
      auto time = std::chrono::high_resolution_clock::now();
      auto deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(time - prevTime).count() / 1000.0f;
      prevTime = time;

      if (animationPlaying) {
        t += 0.0001 * deltaTime;
        if (t > 1.0f) {
          t = 1.0f;
          animationPlaying = false;
        }

        auto step = 1.0f / static_cast<float>(vertexCnt - 1);
        auto i = static_cast<size_t>(t / step);
        if(i >= vertexCnt - 1)
          i = vertexCnt - 2;
        auto lambda = (t - static_cast<float>(i) * step)  / step;
        std::cout << i << ' ' << lambda << '\n'; 

        auto p = bezier1.getPosition(t);
        pBezierObject->position = {p(0), p(1), p(2)};
        pBezierObject->position.x *= -1;
        pBezierObject->position.y *= -1;

        pBezierObject->rotation = rotations[i] * (1.0f - lambda) + rotations[i+1] * lambda;
      }

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