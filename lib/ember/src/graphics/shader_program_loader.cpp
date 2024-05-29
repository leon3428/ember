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
  if (idn == "projectionSpaceCulling"_id) {
    // clang-format off
    Shader shaders[] = {
      makeShaderFromFile(GL_VERTEX_SHADER, shaderFolder + "/projectionSpaceCullingShader.vert"),
      makeShaderFromFile(GL_GEOMETRY_SHADER, shaderFolder + "/projectionSpaceCullingShader.geom"),
      makeShaderFromFile(GL_FRAGMENT_SHADER, shaderFolder + "/solidColorShader.frag")
    };
    // clang-format on

    return {shaders};
  }

  if (idn == "sceneSpaceCulling"_id) {
    // clang-format off
    Shader shaders[] = {
      makeShaderFromFile(GL_VERTEX_SHADER, shaderFolder + "/sceneSpaceCulling.vert"),
      makeShaderFromFile(GL_GEOMETRY_SHADER, shaderFolder + "/sceneSpaceCulling.geom"),
      makeShaderFromFile(GL_FRAGMENT_SHADER, shaderFolder + "/solidColorShader.frag")
    };
    // clang-format on

    return {shaders};
  }

  if (idn == "constantPhongShaderProgram"_id) {
    // clang-format off
    Shader shaders[] = {
      makeShaderFromFile(GL_VERTEX_SHADER, shaderFolder + "/sceneSpaceCulling.vert"),
      makeShaderFromFile(GL_GEOMETRY_SHADER, shaderFolder + "/faceNormal.geom"),
      makeShaderFromFile(GL_FRAGMENT_SHADER, shaderFolder + "/constantPhong.frag")
    };
    // clang-format on

    return {shaders};
  }

  if (idn == "gouraudPhongShaderProgram"_id) {
    // clang-format off
    Shader shaders[] = {
      makeShaderFromFile(GL_VERTEX_SHADER, shaderFolder + "/gouraud.vert"),
      makeShaderFromFile(GL_FRAGMENT_SHADER, shaderFolder + "/constantPhong.frag")
    };
    // clang-format on

    return {shaders};
  }

  if (idn == "phongShaderProgram"_id) {
    // clang-format off
    Shader shaders[] = {
      makeShaderFromFile(GL_VERTEX_SHADER, shaderFolder + "/phong.vert"),
      makeShaderFromFile(GL_FRAGMENT_SHADER, shaderFolder + "/phong.frag")
    };
    // clang-format on

    return {shaders};
  }

  throw std::runtime_error("Invalid shader program identifier");
}
