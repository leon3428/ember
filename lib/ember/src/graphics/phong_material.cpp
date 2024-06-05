#include "phong_material.hpp"

#include <glad/glad.h>
#include <glm/glm/gtc/type_ptr.hpp>
#include "../resource_manager/resource_manager.hpp"

ember::PhongMaterial::PhongMaterial()
    : Material(getResourceManager()->getShaderProgram("phongShaderProgram"_id)),
      ambientColor(0.0f),
      diffuseColor(0.0f),
      specularColor(0.0f),
      shininess(0.0f),
      m_ambientColorLocation(glGetUniformLocation(m_pShaderProgram->getShaderProgramId(), "u_ambientColor")),
      m_diffuseColorLocation(glGetUniformLocation(m_pShaderProgram->getShaderProgramId(), "u_diffuseColor")),
      m_specularColorLocation(glGetUniformLocation(m_pShaderProgram->getShaderProgramId(), "u_specularColor")),
      m_shininessLocation(glGetUniformLocation(m_pShaderProgram->getShaderProgramId(), "u_shininess")),
      m_modelLocation(glGetUniformLocation(m_pShaderProgram->getShaderProgramId(), "u_model")),
      m_modelInvLocation(glGetUniformLocation(m_pShaderProgram->getShaderProgramId(), "u_modelInv")),
      m_shadowMapLocation(glGetUniformLocation(m_pShaderProgram->getShaderProgramId(), "shadowMap")),
      m_diffuseMapLocation(glGetUniformLocation(m_pShaderProgram->getShaderProgramId(), "diffuseTexture")),
      m_normalMapLocation(glGetUniformLocation(m_pShaderProgram->getShaderProgramId(), "normalMap")) {}

auto ember::PhongMaterial::uploadUniforms(const glm::mat4 &model, const glm::mat4 &modelInv) const -> void {
  glUniformMatrix4fv(m_modelLocation, 1, GL_FALSE, glm::value_ptr(model));
  glUniformMatrix4fv(m_modelInvLocation, 1, GL_FALSE, glm::value_ptr(modelInv));

  glUniform3fv(m_ambientColorLocation, 1, &ambientColor[0]);
  glUniform3fv(m_diffuseColorLocation, 1, &diffuseColor[0]);
  glUniform3fv(m_specularColorLocation, 1, &specularColor[0]);
  glUniform1f(m_shininessLocation, shininess);
  glUniform1i(m_shadowMapLocation, 0);
  glUniform1i(m_diffuseMapLocation, 1);
  glUniform1i(m_normalMapLocation, 2);

  glActiveTexture(GL_TEXTURE1);
  m_pDiffuseTexture->bind();
  glActiveTexture(GL_TEXTURE2);
  m_pNormalMap->bind();
}
