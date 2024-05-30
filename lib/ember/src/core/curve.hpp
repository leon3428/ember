#ifndef CURVE_HPP
#define CURVE_HPP

#include <eigen3/Eigen/Dense>

namespace ember {

class ICurve {
public:
  virtual ~ICurve() = default;
  virtual auto getPosition(float t) const -> Eigen::Vector3f = 0;
};

}

#endif // CURVE_HPP