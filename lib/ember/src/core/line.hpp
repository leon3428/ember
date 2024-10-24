#ifndef LINE_HPP
#define LINE_HPP

#include <eigen3/Eigen/Dense>
#include "curve.hpp"

namespace ember {

class Line : public ICurve {
public:
  Line();
  Line(float length);

  virtual auto getPosition(float t) const -> Eigen::Vector3f override;

private:
  float m_length;
};


}

#endif // LINE_HPP