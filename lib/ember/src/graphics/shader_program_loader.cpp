#include "shader_program_loader.hpp"
#include <GL/glext.h>
#include <stdexcept>

#include "../config.hpp"
#include "shader.hpp"

auto ember::shader_program::load(Identifier idn) -> ember::ShaderProgram {
  std::string shaderFolder = config::shaderFolder;

  if (idn == "solidColor"_id) {
    // clang-format off
    Shader solidColorShaders[] = {
      makeShaderFromFile(GL_VERTEX_SHADER, shaderFolder + "/simple.vert"),
      makeShaderFromFile(GL_FRAGMENT_SHADER, shaderFolder + "/solidColorShader.frag")
    };
    // clang-format on

    return {solidColorShaders, 0};
  }
  if (idn == "vertexColor"_id) {
    // clang-format off
    Shader vertexColorShaders[] = {
      makeShaderFromFile(GL_VERTEX_SHADER, shaderFolder + "/vertexColorShader.vert"),
      makeShaderFromFile(GL_FRAGMENT_SHADER, shaderFolder + "/vertexColorShader.frag")
    };
    // clang-format on

    return {vertexColorShaders, 1};
  }

  if (idn == "phongShaderProgram"_id) {
    // clang-format off
    Shader shaders[] = {
      makeShaderFromFile(GL_VERTEX_SHADER, shaderFolder + "/phong.vert"),
      makeShaderFromFile(GL_FRAGMENT_SHADER, shaderFolder + "/phong.frag")
    };
    // clang-format on

    return {shaders, 2};
  }

  if (idn == "shadowMapShaderProgram"_id) {
    // clang-format off
    Shader shaders[] = {
      makeShaderFromFile(GL_VERTEX_SHADER, shaderFolder + "/shadowMap.vert"),
      makeShaderFromFile(GL_FRAGMENT_SHADER, shaderFolder + "/empty.frag")
    };
    // clang-format on

    return {shaders, 3};
  }

  throw std::runtime_error("Invalid shader program identifier");
}
