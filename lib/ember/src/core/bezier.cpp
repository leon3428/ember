#include "bezier.hpp"
#include <eigen3/Eigen/src/Core/Matrix.h>
#include "utils.hpp"

auto ember::BernsteinWeightFunction(int n, int i, float t) -> float {
  return static_cast<float>(binomialCoefficient(n, i)) * std::pow(t, i) * std::pow(1.0f - t, n - i);
}

auto ember::Bezier::addControlPoint(Eigen::Vector3f p) -> void {
  size_t numPoints = m_controlPoints.rows() + 1;
  m_controlPoints.conservativeResize(numPoints, 3);
  m_controlPoints.row(numPoints - 1) = p;
}

auto ember::Bezier::addInterpolatedPoint(Eigen::Vector3f p) -> void {
  size_t numPoints = m_interpolationPoints.rows() + 1;
  m_interpolationPoints.conservativeResize(numPoints, 3);
  m_controlPoints.resize(numPoints, 3);
  m_interpolationPoints.row(numPoints - 1) = p;

  Eigen::MatrixXf mat(numPoints, numPoints);
  for (size_t i = 0; i < numPoints; i++) {
    auto t = static_cast<float>(i) / static_cast<float>(numPoints - 1);

    for (size_t j = 0; j < numPoints; j++) {
      mat(i, j) = BernsteinWeightFunction(numPoints - 1, j, t);
    }
  }

  m_controlPoints = mat.inverse() * m_interpolationPoints;
}

auto ember::Bezier::getPosition(float t) const -> Eigen::Vector3f {
  Eigen::Vector3f pos;
  pos << 0.0f, 0.0f, 0.0f;

  size_t numPoints = m_controlPoints.rows();
  for (size_t i = 0; i < numPoints; i++) {
    pos += BernsteinWeightFunction(numPoints - 1, i, t) * m_controlPoints.row(i);
  }

  return pos;
}