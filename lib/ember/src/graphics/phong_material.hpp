#ifndef PHONG_MATERIAL_HPP
#define PHONG_MATERIAL_HPP

#include <glm/glm.hpp>
#include "material.hpp"
#include "texture.hpp"

namespace ember {
class PhongMaterial : public Material {
 public:
  PhongMaterial();

  glm::vec3 ambientColor;
  glm::vec3 diffuseColor;
  glm::vec3 specularColor;
  float shininess;

  virtual auto uploadUniforms(const glm::mat4 &model, const glm::mat4 &modelInv) const
      -> void override;

  inline auto setDiffuseTexture(const Texture *pTexture) { m_pDiffuseTexture = pTexture; }
  inline auto setNormalMap(const Texture *pTexture) { m_pNormalMap = pTexture; }

 private:
  const Texture *m_pDiffuseTexture;
  const Texture *m_pNormalMap;

  int m_ambientColorLocation;
  int m_diffuseColorLocation;
  int m_specularColorLocation;
  int m_shininessLocation;
  int m_modelLocation;
  int m_modelInvLocation;
  int m_shadowMapLocation;
  int m_diffuseMapLocation;
  int m_normalMapLocation;
};
}  // namespace ember

#endif  // PHONG_MATERIAL_HPP