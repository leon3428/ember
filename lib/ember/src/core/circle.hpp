#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <eigen3/Eigen/Dense>
#include "curve.hpp"

namespace ember {

class Circle : public ICurve {
public:
  Circle();
  Circle(float radius);

  virtual auto getPosition(float t) const -> Eigen::Vector3f override;

private:
  float m_radius;
};


}

#endif // CIRCLE_HPP