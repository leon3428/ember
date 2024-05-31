#include "vertex_color_material.hpp"

#include <glad/glad.h>
#include <glm/glm/gtc/type_ptr.hpp>
#include "../resource_manager/resource_manager.hpp"

ember::VertexColorMaterial::VertexColorMaterial()
    : Material(getResourceManager()->getShaderProgram("vertexColor"_id)),
      m_mvpLocation(glGetUniformLocation(m_pShaderProgram->getShaderProgramId(), "u_mvp")) {}

auto ember::VertexColorMaterial::uploadUniforms(const glm::mat4 &transform, const glm::mat4 &, const glm::mat4 &projection) const -> void {
  auto mvp = projection * transform;
  glUniformMatrix4fv(m_mvpLocation, 1, GL_FALSE, glm::value_ptr(mvp));
}
