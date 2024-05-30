#include "curve_node.hpp"
#include "glm/fwd.hpp"
#include "renderable.hpp"

ember::CurveNode::CurveNode(const ICurve *pCurve, size_t numSamples)
    : m_pCurve(pCurve), m_numSamples(numSamples), m_points(numSamples), m_curveStrip(m_points) {
  m_pCurveRenderable = emplaceChild<Renderable>();
  m_curveMaterial.color = {1.0f, 0.11f, 0.85f, 1.0f};
  m_pCurveRenderable->pVertexArray = &m_curveStrip;
  m_pCurveRenderable->pMaterial = &m_curveMaterial;
  m_pCurveRenderable->vertexCnt = 0;
  m_pCurveRenderable->byteOffset = 0;

  update();
}

auto ember::CurveNode::update() -> void {
  for (size_t i = 0; i < m_numSamples; i++) {
    float t = static_cast<float>(i) / static_cast<float>(m_numSamples - 1);
    auto p = m_pCurve->getPosition(t);
    m_points[i].pos.x = p(0);
    m_points[i].pos.y = p(1);
    m_points[i].pos.z = p(2);
  }

  m_curveStrip.writeVertices(0, m_points);
  m_pCurveRenderable->vertexCnt = m_numSamples;
}