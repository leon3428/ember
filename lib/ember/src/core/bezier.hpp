#ifndef BEZIER_HPP
#define BEZIER_HPP

#include <eigen3/Eigen/Dense>

namespace ember {

auto BernsteinWeightFunction(int n, int i, float t) -> float;

class Bezier {
 public:
  auto addControlPoint(Eigen::Vector3f p) -> void;
  auto addInterpolatedPoint(Eigen::Vector3f p) -> void;
  auto getPosition(float t) const -> Eigen::Vector3f;

  [[nodiscard]] inline auto getControlPoints() const -> const Eigen::MatrixXf & { return m_controlPoints; }
  [[nodiscard]] inline auto getInterpolatedPoints() const -> const Eigen::MatrixXf & { return m_interpolationPoints; }

 private:
  Eigen::MatrixXf m_controlPoints;
  Eigen::MatrixXf m_interpolationPoints;
};

}  // namespace ember

#endif  // BEZIER_HPP