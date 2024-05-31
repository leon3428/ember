#include "shadow_map_material.hpp"

#include <glad/glad.h>
#include <glm/glm/gtc/type_ptr.hpp>
#include "../resource_manager/resource_manager.hpp"

ember::ShadowMapMaterial::ShadowMapMaterial()
    : Material(getResourceManager()->getShaderProgram("shadowMapShaderProgram"_id)),
      m_modelLocation(glGetUniformLocation(m_pShaderProgram->getShaderProgramId(), "u_model")) {}

auto ember::ShadowMapMaterial::uploadUniforms(const glm::mat4 &model, const glm::mat4 &) const -> void {
  glUniformMatrix4fv(m_modelLocation, 1, GL_FALSE, glm::value_ptr(model));
}
