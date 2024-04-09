#include "solid_color_material.hpp"

#include <glad/glad.h>
#include "../config.hpp"
#include "../resource_manager/resource_manager.hpp"
#include "shader_program_loader.hpp"

ember::SolidColorMaterial::SolidColorMaterial()
    : Material(*getResourceManager().getShaderProgram("solidColor"_id)),
      color(1.0f, 0.0f, 0.0f, 1.0f),
      m_colorLocation(glGetUniformLocation(m_shaderProgram.getShaderProgramId(), "u_color")) {}

auto ember::SolidColorMaterial::uploadUniforms() const -> void { glUniform4fv(m_colorLocation, 1, &color[0]); }