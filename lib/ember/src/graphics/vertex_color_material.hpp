#ifndef VERTEX_COLOR_MATERIAL_HPP
#define VERTEX_COLOR_MATERIAL_HPP

#include <glm/glm.hpp>
#include "material.hpp"

namespace ember {
class VertexColorMaterial : public Material {
 public:
  VertexColorMaterial();

  virtual auto uploadUniforms(const glm::mat4 &transform, const glm::mat4 &transformInv, const glm::mat4 &projection) const
      -> void override;

 private:
  int m_mvpLocation;
};
}  // namespace ember

#endif  // VERTEX_COLOR_MATERIAL_HPP