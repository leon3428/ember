#ifndef CUBIC_B_SPLINE_HPP
#define CUBIC_B_SPLINE_HPP

#include <eigen3/Eigen/Dense>
#include "curve.hpp"

namespace ember {

class CubicBSpline : public ICurve {
 public:
  CubicBSpline() = default;
  CubicBSpline(const Eigen::MatrixXf& controlPoints);

  auto addControlPoint(Eigen::Vector3f p) -> void;

  virtual auto getPosition(float t) const -> Eigen::Vector3f override;

 private:
  Eigen::MatrixXf m_controlPoints;

  static const Eigen::Matrix4f m_B;
};

}  // namespace ember

#endif  // CUBIC_B_SPLINE_HPP