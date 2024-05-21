#ifndef BEZIER_CURVE_HPP
#define BEZIER_CURVE_HPP

#include <glm/glm.hpp>
#include <vector>
#include "object3d.hpp"

namespace ember {

class BezierCurve : public Object3d {
 public:
  BezierCurve();

  std::vector<glm::vec3> points;
};

}  // namespace ember

#endif  // BEZIER_CURVE_HPP