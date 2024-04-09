#include "solid_color_material.hpp"

#include <glad/glad.h>
#include <glm/glm/gtc/type_ptr.hpp>
#include "../config.hpp"
#include "../resource_manager/resource_manager.hpp"
#include "shader_program_loader.hpp"

ember::SolidColorMaterial::SolidColorMaterial()
    : Material(*getResourceManager().getShaderProgram("solidColor"_id)),
      color(1.0f, 0.0f, 0.0f, 1.0f),
      m_colorLocation(glGetUniformLocation(m_shaderProgram.getShaderProgramId(), "u_color")),
      m_mvpLocation(glGetUniformLocation(m_shaderProgram.getShaderProgramId(), "u_mvp")) {}

auto ember::SolidColorMaterial::uploadUniforms() const -> void { glUniform4fv(m_colorLocation, 1, &color[0]); }

auto ember::SolidColorMaterial::uploadMvp(const glm::mat4 &mvp) const -> void {
  glUniformMatrix4fv(m_mvpLocation, 1, GL_FALSE, glm::value_ptr(mvp));
}
