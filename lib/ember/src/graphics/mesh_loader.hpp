#ifndef MESH_LOADER_HPP
#define MESH_LOADER_HPP

#include "../core/utils.hpp"
#include "../resource_manager/resource_map.hpp"
#include "static_mesh.hpp"

namespace ember::static_mesh {

auto load(Identifier idn, const ResourceMap &resourceMap) -> StaticMesh;

}  // namespace ember::mesh

#endif  // MESH_LOADER_HPP