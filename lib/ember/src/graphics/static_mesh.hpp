#ifndef STATIC_MESH_HPP
#define STATIC_MESH_HPP

#include "mesh.hpp"

namespace ember {

class StaticMesh : public Mesh {
 public:
  template <Vertex T>
  StaticMesh(std::span<T> vertices, std::span<uint32_t> indices) : Mesh(vertices, indices, GL_STATIC_DRAW) {}
};

}  // namespace ember

#endif  // STATIC_MESH_HPP