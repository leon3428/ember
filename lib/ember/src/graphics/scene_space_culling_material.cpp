#include "scene_space_culling_material.hpp"

#include <glad/glad.h>
#include <glm/glm/gtc/type_ptr.hpp>
#include "../resource_manager/resource_manager.hpp"

ember::SceneSpaceCullingMaterial::SceneSpaceCullingMaterial()
    : Material(getResourceManager()->getShaderProgram("sceneSpaceCulling"_id)),
      color(1.0f, 0.0f, 0.0f, 1.0f),
      m_colorLocation(glGetUniformLocation(m_pShaderProgram->getShaderProgramId(), "u_color")),
      m_mvLocation(glGetUniformLocation(m_pShaderProgram->getShaderProgramId(), "u_mv")),
      m_pLocation(glGetUniformLocation(m_pShaderProgram->getShaderProgramId(), "u_p")) {}

auto ember::SceneSpaceCullingMaterial::uploadUniforms() const -> void {
  glUniform4fv(m_colorLocation, 1, &color[0]);
}

auto ember::SceneSpaceCullingMaterial::uploadMvp(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &projection) const -> void {
  auto mv = view * model;
  glUniformMatrix4fv(m_mvLocation, 1, GL_FALSE, glm::value_ptr(mv));
  glUniformMatrix4fv(m_pLocation, 1, GL_FALSE, glm::value_ptr(projection));
}
