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

    // auto pLight = scene.emplaceChild<ember::Light>();
    // pLight->diffuseIntensity = {0.5f, 0.0f, 0.0f, 1.0f};
    // pLight->specularIntensity = {0.5f, 0.0f, 0.0f, 1.0f};
    // pLight->angle = glm::radians(75.0f);
    // pLight->setPosY(8);
    // pLight->lookAt({0.0f, 0.0f, 0.0f});

    // auto pAnotherLight = scene.emplaceChild<ember::Light>();
    // pAnotherLight->diffuseIntensity = {0.0f, 0.0f, 0.5f, 1.0f};
    // pAnotherLight->specularIntensity = {0.0f, 0.0f, 0.5f, 1.0f};
    // pAnotherLight->angle = glm::radians(75.0f);
    // pAnotherLight->setPosY(8);
    // pAnotherLight->setPosX(5);
    // pAnotherLight->lookAt({5.0f, 0.0f, 0.0f});

    auto pLight = scene.emplaceChild<ember::Light>();
    pLight->diffuseIntensity = {0.5f, 0.0f, 0.0f, 1.0f};
    pLight->specularIntensity = {0.5f, 0.0f, 0.0f, 1.0f};
    pLight->angle = glm::radians(75.0f);
    pLight->setPosY(8);
    pLight->lookAt({0.0f, 0.0f, 0.0f});

    auto pAnotherLight = scene.emplaceChild<ember::Light>();
    pAnotherLight->diffuseIntensity = {1.0f, 1.0f, 1.5f, 1.0f};
    pAnotherLight->specularIntensity = {1.0f, 1.0f, 1.5f, 1.0f};
    pAnotherLight->angle = glm::radians(75.0f);
    pAnotherLight->setPosY(8);
    pAnotherLight->setPosZ(5);
    pAnotherLight->lookAt({5.0f, 0.0f, 0.0f});

    auto pProgram = ember::getResourceManager()->getShaderProgram("phongShaderProgram"_id);
    GLuint programID = pProgram->getShaderProgramId();
    GLuint blockIndex = glGetUniformBlockIndex(programID, "Scene");

    // Get the number of active uniforms in the block
    GLint numUniforms;
    glGetActiveUniformBlockiv(programID, blockIndex, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &numUniforms);

    // Get the indices of the active uniforms
    std::vector<GLuint> indices(numUniforms);
    glGetActiveUniformBlockiv(programID, blockIndex, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES,
                              reinterpret_cast<GLint *>(indices.data()));

    // Query offsets for each uniform in the block
    std::vector<GLint> offsets(numUniforms);
    glGetActiveUniformsiv(programID, numUniforms, indices.data(), GL_UNIFORM_OFFSET, offsets.data());

    // Query names of the active uniforms
    std::vector<GLchar> nameData(256);
    std::vector<GLint> nameLengths(numUniforms);
    glGetActiveUniformsiv(programID, numUniforms, indices.data(), GL_UNIFORM_NAME_LENGTH, nameLengths.data());

    std::vector<std::string> names(numUniforms);
    for (int i = 0; i < numUniforms; ++i) {
      nameData.resize(nameLengths[i]);
      glGetActiveUniformName(programID, indices[i], nameData.size(), nullptr, nameData.data());
      names[i] = std::string(nameData.begin(), nameData.end());
    }

    // Print the offsets for debugging
    for (int i = 0; i < numUniforms; ++i) {
      std::cout << "Uniform name: " << names[i] << ", offset: " << offsets[i] << std::endl;
    }

    std::cout << "Camera pv: " << offsetof(ember::SceneData, camera_pv) << '\n';
    std::cout << "Ambient intensity: " << offsetof(ember::SceneData, ambientIntensity) << '\n';
    std::cout << "Lights[0] diffuse: " << offsetof(ember::SceneData, lights[0].diffuseIntensity) << '\n';
    std::cout << "Lights[0] direction: " << offsetof(ember::SceneData, lights[0].direction) << '\n';
    // std::cout << "Lights[0] cosAngle: " << offsetof(ember::SceneData, lights[0].cosAngle) << '\n';
    std::cout << "Lights[1] diffuse: " << offsetof(ember::SceneData, lights[1].diffuseIntensity) << '\n';
    std::cout << "Lights[2] diffuse: " << offsetof(ember::SceneData, lights[2].diffuseIntensity) << '\n';
    std::cout << "Light cnt: " << offsetof(ember::SceneData, lightCnt) << '\n';

    auto headNode = ember::loadObject("crate"_id);
    // auto pCube = static_cast<ember::Renderable *>(headNode.getChild(0));
    scene.steal(headNode);

    ember::Circle cameraCurve(5.0f);
    scene.emplaceChild<ember::CurveNode>(&cameraCurve, 50);

    ember::ObjectController objController(pAnotherLight, window);

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