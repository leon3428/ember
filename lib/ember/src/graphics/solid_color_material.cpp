#include "solid_color_material.hpp"

#include <glad/glad.h>
#include <glm/glm/gtc/type_ptr.hpp>
#include "../resource_manager/resource_manager.hpp"

ember::SolidColorMaterial::SolidColorMaterial()
    : Material(getResourceManager()->getShaderProgram("solidColor"_id)),
      color(1.0f, 0.0f, 0.0f, 1.0f),
      m_colorLocation(glGetUniformLocation(m_pShaderProgram->getShaderProgramId(), "u_color")),
      m_modelLocation(glGetUniformLocation(m_pShaderProgram->getShaderProgramId(), "u_model")) {}

auto ember::SolidColorMaterial::uploadUniforms(const glm::mat4 &model, const glm::mat4 &) const -> void {
  glUniformMatrix4fv(m_modelLocation, 1, GL_FALSE, glm::value_ptr(model));
  glUniform4fv(m_colorLocation, 1, &color[0]);
}
