#include "cubic_b_spline.hpp"

ember::CubicBSpline::CubicBSpline(const Eigen::MatrixXf &controlPoints) : m_controlPoints(controlPoints) {}

auto ember::CubicBSpline::addControlPoint(Eigen::Vector3f p) -> void {
  size_t numPoints = m_controlPoints.rows() + 1;
  m_controlPoints.conservativeResize(numPoints, 3);
  m_controlPoints.row(numPoints - 1) = p;
}

// clang-format off
const Eigen::Matrix4f ember::CubicBSpline::m_B = (Eigen::Matrix4f() << 
  -1.0f / 6.0f,  3.0f / 6.0f, -3.0f / 6.0f, 1.0f / 6.0f, 
   3.0f / 6.0f, -6.0f / 6.0f,  3.0f / 6.0f, 0.0f / 6.0f, 
  -3.0f / 6.0f,  0.0f / 6.0f,  3.0f / 6.0f, 0.0f / 6.0f, 
   1.0f / 6.0f,  4.0f / 6.0f,  1.0f / 6.0f, 0.0f / 6.0f
).finished();
// clang-format on

auto ember::CubicBSpline::getPosition(float t) const -> Eigen::Vector3f {
  auto segmentCnt = static_cast<size_t>(m_controlPoints.rows()) - 3;
  auto tPerSegment = 1.0f / static_cast<float>(segmentCnt);
  auto firstPoint = static_cast<size_t>(t / tPerSegment);
  if (firstPoint == segmentCnt) firstPoint--;
  auto segT = (t - static_cast<float>(firstPoint) * tPerSegment) / tPerSegment;

  Eigen::RowVector4f t_vec;
  t_vec << std::pow(segT, 3), std::pow(segT, 2), segT, 1.0f;

  return t_vec * m_B * m_controlPoints.block(firstPoint, 0, 4, 3);
}

auto ember::CubicBSpline::getTangent(float t) const -> Eigen::Vector3f {
  auto segmentCnt = static_cast<size_t>(m_controlPoints.rows()) - 3;
  auto tPerSegment = 1.0f / static_cast<float>(segmentCnt);
  auto firstPoint = static_cast<size_t>(t / tPerSegment);
  if (firstPoint == segmentCnt) firstPoint--;
  auto segT = (t - static_cast<float>(firstPoint) * tPerSegment) / tPerSegment;

  Eigen::RowVector4f t_vec;
  t_vec << 3.0f * std::pow(segT, 2), 2.0f * segT, 1.0f, 0.0f;

  return t_vec * m_B * m_controlPoints.block(firstPoint, 0, 4, 3);
}