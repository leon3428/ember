#ifndef OBJECT_LOADER_HPP
#define OBJECT_LOADER_HPP

#include "../core/utils.hpp"
#include "node.hpp"

namespace ember {

auto loadObject(Identifier idn) -> Node;

}  // namespace ember

#endif  // OBJECT_LOADER_HPP