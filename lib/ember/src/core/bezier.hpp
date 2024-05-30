#ifndef BEZIER_HPP
#define BEZIER_HPP

#include <eigen3/Eigen/Dense>
#include "curve.hpp"

namespace ember {

auto BernsteinWeightFunction(int n, int i, float t) -> float;

class Bezier : public ICurve {
 public:
  auto addControlPoint(Eigen::Vector3f p) -> void;
  auto addInterpolatedPoint(Eigen::Vector3f p) -> void;
  virtual auto getPosition(float t) const -> Eigen::Vector3f override;

  [[nodiscard]] inline auto getControlPoints() const -> const Eigen::MatrixXf & { return m_controlPoints; }
  [[nodiscard]] inline auto getInterpolatedPoints() const -> const Eigen::MatrixXf & { return m_interpolationPoints; }
  [[nodiscard]] inline auto getPointCount() const -> size_t { return m_controlPoints.rows(); }

 private:
  Eigen::MatrixXf m_controlPoints;
  Eigen::MatrixXf m_interpolationPoints;
};

}  // namespace ember

#endif  // BEZIER_HPP