#ifndef BEZIER_CURVE_HPP
#define BEZIER_CURVE_HPP

#include <glm/glm.hpp>
#include <vector>
#include "dynamic_line_strip.hpp"
#include "object3d.hpp"
#include "renderable.hpp"
#include "solid_color_material.hpp"
#include "vertex_types.hpp"

namespace ember {

auto BernsteinWeightFunction(int n, int i, float t) -> float;

class BezierCurve : public Object3d {
 public:
  BezierCurve(size_t maxSize, size_t numSamples);

  auto addPoint(const glm::vec3 &pos, const glm::quat &rot) -> void;
  auto getPosition(float t) const -> glm::vec3;

 private:
  size_t m_numPoints;
  size_t m_numSamples;

  std::vector<PosVertex> m_pos;
  std::vector<glm::quat> m_rot;
  std::vector<PosVertex> m_curve;

  DynamicLineStrip<PosVertex> m_controlPoligonStrip;
  Renderable *m_pContorlPoligonRenderable;
  SolidColorMaterial m_controlPoligonMaterial;

  DynamicLineStrip<PosVertex> m_curveStrip;
  Renderable *m_pCurveRenderable;
  SolidColorMaterial m_curveMaterial;
};

}  // namespace ember

#endif  // BEZIER_CURVE_HPP