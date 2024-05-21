#include "bezier_curve.hpp"

ember::BezierCurve::BezierCurve() {
  m_attributes |= static_cast<unsigned>(NodeAttribute::Bezier);
}
