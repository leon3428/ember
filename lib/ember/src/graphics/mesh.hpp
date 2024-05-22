#ifndef MESH_HPP
#define MESH_HPP

#include <span>
#include "vertex_array.hpp"

namespace ember {

class Mesh : public VertexArray {
 public:
  template <Vertex T>
  Mesh(std::span<T> vertices, std::span<const uint32_t> indices) : VertexArray(vertices, {indices}, GL_STATIC_DRAW) {}

  [[nodiscard]] inline virtual auto getPrimitiveType() const  -> GLenum override { return GL_TRIANGLES; }

 private:
};

}  // namespace ember

#endif  // MESH_HPP