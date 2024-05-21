#ifndef DYNAMIC_LINE_STRIP_HPP
#define DYNAMIC_LINE_STRIP_HPP

#include <span>
#include "vertex_array.hpp"

namespace ember {

template <Vertex T>
class DynamicLineStrip : public VertexArray {
 public:
  DynamicLineStrip(std::span<T> vertices) : VertexArray(vertices, {}, GL_DYNAMIC_DRAW) {}

  auto writeVertex(size_t i, const T &vertex) -> void {
    m_vertexBuffer.bind();
    glBufferSubData(GL_ARRAY_BUFFER, i * sizeof(T), sizeof(T), &vertex);
    m_vertexBuffer.unbind();
  }

  auto writeVertices(size_t i, std::span<T> vertices) {
    m_vertexBuffer.bind();
    glBufferSubData(GL_ARRAY_BUFFER, i * sizeof(T), vertices.size_bytes(), vertices.data());
    m_vertexBuffer.unbind();
  }

  [[nodiscard]] inline virtual auto getPrimitiveType() const  -> GLenum override { return GL_LINE_STRIP; };
};

}  // namespace ember

#endif  // DYNAMIC_LINE_STRIP_HPP