#include "projection_space_culling_material.hpp"

#include <glad/glad.h>
#include <glm/glm/gtc/type_ptr.hpp>
#include "../resource_manager/resource_manager.hpp"

ember::ProjectionSpaceCullingMaterial::ProjectionSpaceCullingMaterial()
    : Material(getResourceManager()->getShaderProgram("projectionSpaceCulling"_id)),
      color(1.0f, 0.0f, 0.0f, 1.0f),
      m_colorLocation(glGetUniformLocation(m_shaderProgram.getShaderProgramId(), "u_color")),
      m_mvpLocation(glGetUniformLocation(m_shaderProgram.getShaderProgramId(), "u_mvp")) {}

auto ember::ProjectionSpaceCullingMaterial::uploadUniforms() const -> void {
  glUniform4fv(m_colorLocation, 1, &color[0]);
}

auto ember::ProjectionSpaceCullingMaterial::uploadMvp(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &projection) const -> void {
  auto mvp = projection * view * model;
  glUniformMatrix4fv(m_mvpLocation, 1, GL_FALSE, glm::value_ptr(mvp));
}
