#ifndef Curve_LOADER_HPP
#define Curve_LOADER_HPP

#include <memory>
#include "../core/utils.hpp"
#include "../core/curve.hpp"

namespace ember {

auto loadCurve(Identifier idn) -> std::unique_ptr<ICurve>;

}  // namespace ember

#endif  // Curve_LOADER_HPP