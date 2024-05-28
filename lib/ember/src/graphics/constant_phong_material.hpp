#ifndef CONSTANT_PHONG_MATERIAL_HPP
#define CONSTANT_PHONG_MATERIAL_HPP

#include <glm/glm.hpp>
#include "material.hpp"

namespace ember {
class ConstantPhongMaterial : public Material {
 public:
  ConstantPhongMaterial();

  glm::vec3 ambientColor;
  glm::vec3 diffuseColor;
  glm::vec3 specularColor;
  float shininess;

  virtual auto uploadUniforms() const -> void override;
  virtual auto uploadMvp(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &projection) const
      -> void override;

 private:
  int m_ambientColorLocation;
  int m_diffuseColorLocation;
  int m_specularColorLocation;
  int m_shininessLocation;
  int m_mvLocation;
  int m_pLocation;
};
}  // namespace ember

#endif  // CONSTANT_PHONG_MATERIAL_HPP