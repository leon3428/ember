#include <array>
#include <chrono>
#include <iostream>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "ember.hpp"

int main(int, char *argv[]) {
  std::cout << argv[0] << std::endl;

  {
    auto width = 800;
    auto height = 600;
    ember::Window window("Ember", width, height);
    auto &eventBus = window.getEventBus();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cout << "Failed to initialize GLAD\n";
      return -1;
    }

    glViewport(0, 0, width, height);

    eventBus.subscribe<ember::ResizeEvent>([](const ember::ResizeEvent &e) { glViewport(0, 0, e.width, e.height); });

    auto vendor = glGetString(GL_VENDOR);
    auto renderer = glGetString(GL_RENDERER);
    std::cout << vendor << '\n' << renderer << '\n';

    std::array<ember::PosVertex, 4> vertices = {
        ember::PosVertex{glm::vec3{0.9f, 0.9f, 0.0f}}, ember::PosVertex{glm::vec3{0.9f, 0.8f, 0.0f}},
        ember::PosVertex{glm::vec3{0.8f, 0.8f, 0.0f}}, ember::PosVertex{glm::vec3{0.8f, 0.9f, 0.0f}}};

    uint32_t indices[] = {
        // note that we start from 0!
        0, 1, 3,  // first triangle
        1, 2, 3   // second triangle
    };

    ember::StaticMesh colorSelectorMesh(std::span<ember::PosVertex>{vertices}, indices);

    ember::Shader solidColorShaders[] = {
        ember::makeShaderFromFile(GL_VERTEX_SHADER, "shaders/solidColorShader.vert"),
        ember::makeShaderFromFile(GL_FRAGMENT_SHADER, "shaders/solidColorShader.frag")};

    ember::ShaderProgram solidColorShaderProgram(solidColorShaders);
    auto location = glGetUniformLocation(solidColorShaderProgram.getShaderProgramId(), "u_color");

    // ember::Shader vertexColorShaders[] = {
    // 	ember::makeShaderFromFile(GL_VERTEX_SHADER, "irgLab/vjezba3/shaders/vertexColorShader.vert"),
    // 	ember::makeShaderFromFile(GL_FRAGMENT_SHADER, "irgLab/vjezba3/shaders/vertexColorShader.frag")
    // };

    // ember::ShaderProgram vertexColorShaderProgram(vertexColorShaders);

    ember::Shader vertexColorShaders[] = {
        ember::makeShaderFromFile(GL_VERTEX_SHADER, "shaders/partyShader.vert"),
        ember::makeShaderFromFile(GL_FRAGMENT_SHADER, "shaders/vertexColorShader.frag")};

    ember::ShaderProgram vertexColorShaderProgram(vertexColorShaders);
    auto timeLocation = glGetUniformLocation(vertexColorShaderProgram.getShaderProgramId(), "u_time");

    float r = 1.0f;
    float g = 0.0;
    float b = 0.0;

    eventBus.subscribe<ember::KeyPressedEvent>([&r, &g, &b](const ember::KeyPressedEvent &e) {
      if (e.keyCode == ember::KeyCode::KeyR) r += 0.1;
      if (e.keyCode == ember::KeyCode::KeyG) g += 0.1;
      if (e.keyCode == ember::KeyCode::KeyB) b += 0.1;

      if (r > 1.0) r -= 1.0;
      if (g > 1.0) g -= 1.0;
      if (b > 1.0) b -= 1.0;
    });

    ember::DynamicMesh<ember::PosColVertex> triangles(20, 60);
    ember::PosColVertex v({0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f});
    size_t vertexCount = 0;

    eventBus.subscribe<ember::MouseButtonPressedEvent>(
        [&triangles, &vertexCount, &v](const ember::MouseButtonPressedEvent &e) {
          if (e.keyCode == ember::MouseButtonCode::MouseButtonLeft) {
            triangles.writeVertex(vertexCount++, v);

            if (vertexCount >= 3) {
              auto triangleCnt = vertexCount - 2;
              auto indexCount = 3 * triangleCnt;

              triangles.writeIndex(indexCount - 1, vertexCount - 1);
              triangles.writeIndex(indexCount - 2, vertexCount - 2);
              triangles.writeIndex(indexCount - 3, vertexCount - 3);
            }
          }
        });

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    auto start = std::chrono::system_clock::now();

    while (!window.shouldClose()) {
      glClear(GL_COLOR_BUFFER_BIT);

      solidColorShaderProgram.bind();
      glUniform4f(location, r, g, b, 1.0f);

      colorSelectorMesh.bind();
      glDrawElements(GL_TRIANGLES, colorSelectorMesh.getNumVertices(), GL_UNSIGNED_INT, 0);
      colorSelectorMesh.unbind();

      auto [width, height] = window.getSize();
      auto [xPos, yPos] = window.getMousePos();
      v.pos.x = xPos / width * 2.0f - 1.0f;
      v.pos.y = yPos / height * -2.0f + 1.0f;
      v.col = {r, g, b};

      if (vertexCount >= 3) {
        // std::cout << v2.pos.x << ' ' << v2.pos.y << '\n';
        triangles.writeVertex(vertexCount - 1, v);

        auto triangleCnt = vertexCount - 2;
        auto indexCount = 3 * triangleCnt;

        vertexColorShaderProgram.bind();

        auto time = std::chrono::system_clock::now();
        auto t = std::chrono::duration_cast<std::chrono::milliseconds>(time - start).count() / 1000.0f;
        glUniform1f(timeLocation, t);

        triangles.bind();
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
        triangles.unbind();
      }

      window.update();
    }
  }

  glfwTerminate();

  return 0;
}