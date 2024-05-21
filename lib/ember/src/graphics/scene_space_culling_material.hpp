#ifndef SCENE_SPACE_CULLING_MATERIAL
#define SCENE_SPACE_CULLING_MATERIAL

#include <glm/glm.hpp>
#include "material.hpp"

namespace ember {

class SceneSpaceCullingMaterial : public Material {
 public:
  SceneSpaceCullingMaterial();

  glm::vec4 color;

  virtual auto uploadUniforms() const -> void override;
  virtual auto uploadMvp(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &projection) const -> void override;

 private:
  int m_colorLocation;
  int m_mvLocation;
  int m_pLocation;
};

}  // namespace ember

#endif // SCENE_SPACE_CULLING_MATERIAL