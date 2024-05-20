#include "shader_program_loader.hpp"
#include <stdexcept>

#include "../config.hpp"
#include "shader.hpp"

auto ember::shader_program::load(Identifier idn) -> ember::ShaderProgram {
  std::string shaderFolder = config::shaderFolder;

  if (idn == "solidColor"_id) {
    // clang-format off
    Shader solidColorShaders[] = {
      makeShaderFromFile(GL_VERTEX_SHADER, shaderFolder + "/solidColorShader.vert"),
      makeShaderFromFile(GL_FRAGMENT_SHADER, shaderFolder + "/solidColorShader.frag")
    };
    // clang-format on

    return {solidColorShaders};
  }
  if (idn == "vertexColor"_id) {
    // clang-format off
    Shader vertexColorShaders[] = {
      makeShaderFromFile(GL_VERTEX_SHADER, shaderFolder + "/vertexColorShader.vert"),
      makeShaderFromFile(GL_FRAGMENT_SHADER, shaderFolder + "/vertexColorShader.frag")
    };
    // clang-format on

    return {vertexColorShaders};
  }

  throw std::runtime_error("Invalid shader program identifier");
}
