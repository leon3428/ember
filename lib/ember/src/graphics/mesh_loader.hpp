#ifndef MESH_LOADER_HPP
#define MESH_LOADER_HPP

#include "../core/utils.hpp"
#include "mesh.hpp"

namespace ember::mesh {

auto load(Identifier idn) -> Mesh;

}  // namespace ember::mesh

#endif  // MESH_LOADER_HPP