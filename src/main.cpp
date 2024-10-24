#include <algorithm>
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
#include "glm/ext/quaternion_trigonometric.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "glm/trigonometric.hpp"

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
    pLight->diffuseIntensity = {0.5f, 0.0f, 0.0f, 1.0f};
    pLight->specularIntensity = {0.5f, 0.0f, 0.0f, 1.0f};
    pLight->angle = glm::radians(75.0f);
    pLight->setPosY(8);
    pLight->lookAt({0.0f, 0.0f, 0.0f});

    auto headNode = ember::loadObject("shadowMap2"_id);
    scene.steal(headNode);

    auto pSpline = ember::loadCurve("spiral"_id);
    scene.emplaceChild<ember::CurveNode>(pSpline.get(), 50);

    auto line = ember::Line(5.0f);
    auto pLine = scene.emplaceChild<ember::CurveNode>(&line, 2);
    pLine->setColor({0.0f, 1.0f, 0.0f, 1.0f});
    auto pLineRenderable = pLine->getRenderable();

    auto plane = ember::loadObject("plane"_id);
    scene.steal(plane);
    auto pPlane = static_cast<ember::Renderable *>(scene.getChild(scene.childCnt() - 1));
    auto initialPlaneOrientation = glm::vec3(0.0f, 0.0f, 1.0f);
    ember::SolidColorMaterial redMaterial;
    redMaterial.color = {1.0f, 0.0f, 0.0f, 1.0f};
    pPlane->pMaterial = &redMaterial;
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    auto t = 0.0f;
    auto prevTime = std::chrono::high_resolution_clock::now();

    while (!window.shouldClose()) {
      auto time = std::chrono::high_resolution_clock::now();
      auto deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(time - prevTime).count() / 1000.0f;
      if (deltaTime < 10) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10 - static_cast<int>(deltaTime)));
        time = std::chrono::high_resolution_clock::now();
        deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(time - prevTime).count() / 1000.0f;
      }

      if (window.isKeyPressed(ember::KeyCode::KeyLeft)) t = std::max(t - 0.0001f * deltaTime, 0.0f);
      if (window.isKeyPressed(ember::KeyCode::KeyRight)) t = std::min(t + 0.0001f * deltaTime, 1.0f);

      auto planePostion = pSpline->getPosition(t);
      pPlane->setPosX(planePostion(0));
      pPlane->setPosY(planePostion(1));
      pPlane->setPosZ(planePostion(2));

      pLineRenderable->setPosX(planePostion(0));
      pLineRenderable->setPosY(planePostion(1));
      pLineRenderable->setPosZ(planePostion(2));

      auto curveTangentEigen = static_cast<ember::CubicBSpline *>(pSpline.get())->getTangent(t);
      glm::vec3 curveTangent(curveTangentEigen(0), curveTangentEigen(1), curveTangentEigen(2));
      auto rotationVector = glm::cross(initialPlaneOrientation, curveTangent);
      auto cosAngle = glm::dot(initialPlaneOrientation, curveTangent) / (glm::length(curveTangent));
      auto angle = glm::acos(cosAngle);
      auto rotation = glm::angleAxis(angle, glm::normalize(rotationVector));
      pPlane->setRotation(rotation);
      pLineRenderable->setRotation(rotation);
      prevTime = time;

      cameraController.update(deltaTime);
      renderEngine.render(&scene);

      window.setTitle(std::format("FPS: {}, Frame Time: {}ms", 1000 / deltaTime, deltaTime));
      window.update();
    }

    resourceManager->clear();
  }

  glfwTerminate();
  return 0;
}