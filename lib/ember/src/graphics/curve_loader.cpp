#include "curve_loader.hpp"

#include <fstream>
#include <memory>

#include <eigen3/Eigen/Dense>
#include "../core/cubic_b_spline.hpp"
#include "../resource_manager/resource_index.hpp"

auto ember::loadCurve(Identifier idn) -> std::unique_ptr<ICurve> {
  auto description = getResourceIndex()->getDescription<resource_desc::Curve>(idn);

  if (!description) throw("Curve with that identifier does not exist");

  if (description->curveType == resource_desc::CurveType::CubicBSpline) {
    std::ifstream file(description->path);

    size_t point_cnt;
    file >> point_cnt;

    Eigen::MatrixXf controlPoints(point_cnt, 3);

    for (size_t i = 0; i < point_cnt; i++) {
      float x, y, z;
      file >> x >> y >> z;
      controlPoints(i, 0) = x;
      controlPoints(i, 1) = y;
      controlPoints(i, 2) = z;
    }

    return std::make_unique<CubicBSpline>(controlPoints);
  } else {
    throw("Unknown curve type");
  }
}