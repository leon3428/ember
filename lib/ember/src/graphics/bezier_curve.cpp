#include "bezier_curve.hpp"
#include <memory>
#include "renderable.hpp"

ember::BezierCurve::BezierCurve(size_t size) : m_numPoints(0), m_pos(size), m_rot(size), m_controlPoligon(m_pos) {
  children.push_back(std::make_unique<Renderable>());
  m_pContorlPoligonRenderable = static_cast<Renderable *>(children[0].get());
  m_pContorlPoligonRenderable->pVertexArray = &m_controlPoligon;
  m_pContorlPoligonRenderable->pMaterial = &m_material;
  m_pContorlPoligonRenderable->vertexCnt = 0;
  m_pContorlPoligonRenderable->byteOffset = 0;
}

auto ember::BezierCurve::addPoint(const glm::vec3 &pos, const glm::quat &rot) -> void {
  m_pos[m_numPoints] = {pos};
  m_rot[m_numPoints] = rot;

  m_controlPoligon.writeVertex(m_numPoints, m_pos[m_numPoints]);

  m_numPoints++;

  m_pContorlPoligonRenderable->vertexCnt = m_numPoints;
}