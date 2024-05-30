#ifndef SOLID_COLOR_MATERIAL_HPP
#define SOLID_COLOR_MATERIAL_HPP

#include <glm/glm.hpp>
#include "material.hpp"

namespace ember {
class SolidColorMaterial : public Material {
 public:
  SolidColorMaterial();

  glm::vec4 color;

  virtual auto uploadUniforms(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &projection) const -> void override;

 private:
  int m_colorLocation;
  int m_mvpLocation;
};
}  // namespace ember

#endif  // SOLID_COLOR_MATERIAL_HPP