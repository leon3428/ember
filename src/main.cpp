#include <cstddef>
#include <iostream>
#include <vector>

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ember.hpp"
#include "glm/ext/quaternion_common.hpp"

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

    auto pLight = scene.emplaceChild<ember::Light>();
    pLight->ambientIntensity = {1.0f, 1.0f, 1.0f, 1.0f};
    pLight->diffuseIntensity = {1.0f, 1.0f, 1.0f, 1.0f};
    pLight->specularIntensity = {1.0f, 1.0f, 1.0f, 1.0f};

    auto headNode = ember::loadObject("headObject"_id);
    auto pHead = static_cast<ember::Renderable *>(headNode.getChild(0));
    scene.steal(headNode);

    ember::ObjectController objController(pHead, window);
    auto bezier = ember::Bezier();
    auto pBezierNode = scene.emplaceChild<ember::BezierNode>(bezier, 40);
    ember::Object3d *pBezierObject = pHead;
    bool animationPlaying = false;
    float t = 0.0f;

    std::vector<glm::quat> rotations;

    eventBus.subscribe<ember::KeyPressedEvent>(
        [&bezier, pBezierNode, pBezierObject, &animationPlaying, &t, &rotations](const ember::KeyPressedEvent &e) {
          if (e.keyCode == ember::KeyCode::KeyTab) {
            auto pos = pBezierObject->position;
            pos.x *= -1;
            pos.y *= -1;
            bezier.addInterpolatedPoint({pos.x, pos.y, pos.z});
            pBezierNode->update();
            rotations.push_back(pBezierObject->rotation);

          } else if (e.keyCode == ember::KeyCode::KeySpace) {
            animationPlaying = true;
            t = 0.0f;
          }
        });

    // renderEngine.wireframeMode();
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

        auto pointCnt = bezier.getPointCount();
        auto step = 1.0f / static_cast<float>(pointCnt - 1);
        auto i = static_cast<size_t>(t / step);
        if (i >= pointCnt - 1) i = pointCnt - 2;
        auto lambda = (t - static_cast<float>(i) * step) / step;

        auto p = bezier.getPosition(t);
        pBezierObject->position = {p(0), p(1), p(2)};
        pBezierObject->position.x *= -1;
        pBezierObject->position.y *= -1;

        pBezierObject->rotation = glm::slerp(rotations[i], rotations[i + 1], lambda);
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