#ifndef CURVE_NODE_HPP
#define CURVE_NODE_HPP

#include <glm/glm.hpp>
#include <vector>
#include "../core/curve.hpp"
#include "dynamic_line_strip.hpp"
#include "glm/fwd.hpp"
#include "object3d.hpp"
#include "renderable.hpp"
#include "solid_color_material.hpp"
#include "vertex_types.hpp"

namespace ember {

class CurveNode : public Object3d {
 public:
  CurveNode(const ICurve *pCurve, size_t numSamples);

  auto update() -> void;
  inline auto setColor(glm::vec4 color) { m_curveMaterial.color = color; }

 private:
  const ICurve *m_pCurve;
  size_t m_numSamples;

  std::vector<PosVertex> m_points;

  DynamicLineStrip<PosVertex> m_curveStrip;
  Renderable *m_pCurveRenderable;
  SolidColorMaterial m_curveMaterial;
};

}  // namespace ember

#endif  // CURVE_NODE_HPP