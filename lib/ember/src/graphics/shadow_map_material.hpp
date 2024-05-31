#ifndef SHADOW_MAP_MATERIAL_HPP
#define SHADOW_MAP_MATERIAL_HPP

#include <glm/glm.hpp>
#include "material.hpp"

namespace ember {
class ShadowMapMaterial : public Material {
 public:

  ShadowMapMaterial();
  virtual auto uploadUniforms(const glm::mat4 &model, const glm::mat4 &modelInv) const -> void override;
  
 private:
  int m_modelLocation;
};
}  // namespace ember

#endif  // SHADOW_MAP_MATERIAL_HPP