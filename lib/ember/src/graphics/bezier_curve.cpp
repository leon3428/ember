#include "bezier_curve.hpp"
#include <memory>
#include "../core/utils.hpp"
#include "glm/fwd.hpp"
#include "renderable.hpp"
#include "vertex_types.hpp"

auto ember::BernsteinWeightFunction(int n, int i, float t) -> float {
  return static_cast<float>(binomialCoefficient(n, i)) * std::pow(t, i) * std::pow(1.0f - t, n - i);
}

ember::BezierCurve::BezierCurve(size_t maxSize, size_t numSamples)
    : m_numPoints(0),
      m_numSamples(numSamples),
      m_pos(maxSize),
      m_rot(maxSize),
      m_curve(numSamples),
      m_controlPoligonStrip(m_pos),
      m_curveStrip(std::span<PosVertex>(m_curve)) {
  children.push_back(std::make_unique<Renderable>());
  m_pContorlPoligonRenderable = static_cast<Renderable *>(children[0].get());
  m_controlPoligonMaterial.color = {0.6f, 0.6f, 0.6f, 1.0f};
  m_pContorlPoligonRenderable->pVertexArray = &m_controlPoligonStrip;
  m_pContorlPoligonRenderable->pMaterial = &m_controlPoligonMaterial;
  m_pContorlPoligonRenderable->vertexCnt = 0;
  m_pContorlPoligonRenderable->byteOffset = 0;

  children.push_back(std::make_unique<Renderable>());
  m_pCurveRenderable = static_cast<Renderable *>(children[1].get());
  m_curveMaterial.color = {1.0f, 0.11f, 0.85f, 1.0f};
  m_pCurveRenderable->pVertexArray = &m_curveStrip;
  m_pCurveRenderable->pMaterial = &m_curveMaterial;
  m_pCurveRenderable->vertexCnt = 0;
  m_pCurveRenderable->byteOffset = 0;
}

auto ember::BezierCurve::getPosition(float t) const -> glm::vec3 {
  glm::vec3 p(0.0f);

  for (size_t j = 0; j < m_numPoints; j++) {
    p += BernsteinWeightFunction(m_numPoints - 1, j, t) * m_pos[j].pos;
  }

  return p;
}

auto ember::BezierCurve::addPoint(const glm::vec3 &pos, const glm::quat &rot) -> void {
  m_pos[m_numPoints] = {pos};
  m_rot[m_numPoints] = rot;

  m_controlPoligonStrip.writeVertex(m_numPoints, m_pos[m_numPoints]);
  m_numPoints++;
  m_pContorlPoligonRenderable->vertexCnt = m_numPoints;

  for (size_t i = 0; i < m_numSamples; i++) {
    float t = static_cast<float>(i) / static_cast<float>(m_numSamples - 1);
    m_curve[i].pos = getPosition(t);
  }

  m_curveStrip.writeVertices(0, m_curve);
  m_pCurveRenderable->vertexCnt = m_numSamples;
}