#include "constant_phong_material.hpp"

#include <glad/glad.h>
#include <glm/glm/gtc/type_ptr.hpp>
#include "../resource_manager/resource_manager.hpp"

ember::ConstantPhongMaterial::ConstantPhongMaterial()
    : Material(getResourceManager()->getShaderProgram("constantPhongShaderProgram"_id)),
      ambientColor(0.0f),
      diffuseColor(0.0f),
      specularColor(0.0f),
      shininess(0.0f),
      m_ambientColorLocation(glGetUniformLocation(m_pShaderProgram->getShaderProgramId(), "u_ambientColor")),
      m_diffuseColorLocation(glGetUniformLocation(m_pShaderProgram->getShaderProgramId(), "u_diffuseColor")),
      m_specularColorLocation(glGetUniformLocation(m_pShaderProgram->getShaderProgramId(), "u_specularColor")),
      m_shininessLocation(glGetUniformLocation(m_pShaderProgram->getShaderProgramId(), "u_shininess")),
      m_mvLocation(glGetUniformLocation(m_pShaderProgram->getShaderProgramId(), "u_mv")),
      m_pLocation(glGetUniformLocation(m_pShaderProgram->getShaderProgramId(), "u_p")) {}

auto ember::ConstantPhongMaterial::uploadUniforms() const -> void { 
  glUniform3fv(m_ambientColorLocation, 1, &ambientColor[0]); 
  glUniform3fv(m_diffuseColorLocation, 1, &diffuseColor[0]); 
  glUniform3fv(m_specularColorLocation, 1, &specularColor[0]); 
  glUniform1f(m_shininessLocation, shininess);
}

auto ember::ConstantPhongMaterial::uploadMvp(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &projection) const -> void {
  auto mv = view * model;
  glUniformMatrix4fv(m_mvLocation, 1, GL_FALSE, glm::value_ptr(mv));
  glUniformMatrix4fv(m_pLocation, 1, GL_FALSE, glm::value_ptr(projection));
}
