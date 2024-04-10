#include "vertex_color_material.hpp"

#include <glad/glad.h>
#include <glm/glm/gtc/type_ptr.hpp>
#include "../config.hpp"
#include "../resource_manager/resource_manager.hpp"
#include "shader_program_loader.hpp"

ember::VertexColorMaterial::VertexColorMaterial()
    : Material(*getResourceManager().getShaderProgram("vertexColor"_id)),
      m_mvpLocation(glGetUniformLocation(m_shaderProgram.getShaderProgramId(), "u_mvp")) {}

auto ember::VertexColorMaterial::uploadMvp(const glm::mat4 &mvp) const -> void {
  glUniformMatrix4fv(m_mvpLocation, 1, GL_FALSE, glm::value_ptr(mvp));
}
