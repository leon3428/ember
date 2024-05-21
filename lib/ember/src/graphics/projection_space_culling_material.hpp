#ifndef PROJECTION_SPACE_CULLING_MATERIAL
#define PROJECTION_SPACE_CULLING_MATERIAL

#include <glm/glm.hpp>
#include "material.hpp"

namespace ember {

class ProjectionSpaceCullingMaterial : public Material {
 public:
  ProjectionSpaceCullingMaterial();

  glm::vec4 color;

  virtual auto uploadUniforms() const -> void override;
  virtual auto uploadMvp(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &projection) const -> void override;

 private:
  int m_colorLocation;
  int m_mvpLocation;
};

}  // namespace ember

#endif // PROJECTION_SPACE_CULLING_MATERIAL