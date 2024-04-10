#include "shader_program_loader.hpp"

#include "../config.hpp"
#include "shader.hpp"

auto ember::shader_program::load(Identifier idn, const ResourceMap &resourceMap) -> ember::ShaderProgram {
  auto shaderFolder = resourceMap.getPath("shaderFolder"_id);

  if (shaderFolder) {
    if (idn == "solidColor"_id) {
      Shader solidColorShaders[] = {makeShaderFromFile(GL_VERTEX_SHADER, *shaderFolder / "solidColorShader.vert"),
                                    makeShaderFromFile(GL_FRAGMENT_SHADER, *shaderFolder / "solidColorShader.frag")};

      return {solidColorShaders};
    }
    if (idn == "vertexColor"_id) {
      Shader vertexColorShaders[] = {makeShaderFromFile(GL_VERTEX_SHADER, *shaderFolder / "vertexColorShader.vert"),
                                     makeShaderFromFile(GL_FRAGMENT_SHADER, *shaderFolder / "vertexColorShader.frag")};

      return {vertexColorShaders};
    }
  }

  throw std::runtime_error("Shader with provided id does not exist");
}
