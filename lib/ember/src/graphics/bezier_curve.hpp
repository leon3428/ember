#ifndef BEZIER_CURVE_HPP
#define BEZIER_CURVE_HPP

#include <glm/glm.hpp>
#include <vector>
#include "object3d.hpp"
#include "dynamic_line_strip.hpp"
#include "renderable.hpp"
#include "vertex_types.hpp"
#include "solid_color_material.hpp"

namespace ember {

class BezierCurve : public Object3d {
 public:
  BezierCurve(size_t size);

  auto addPoint(const glm::vec3 &pos, const glm::quat &rot) -> void;
  
 private:
  size_t m_numPoints;

  std::vector<PosVertex> m_pos;
  std::vector<glm::quat> m_rot;

  DynamicLineStrip<PosVertex> m_controlPoligon;
  Renderable *m_pContorlPoligonRenderable;
  SolidColorMaterial m_material;
};

}  // namespace ember

#endif  // BEZIER_CURVE_HPP