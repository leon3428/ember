#ifndef VERTEX_ARRAY_HPP
#define VERTEX_ARRAY_HPP

#include <glad/glad.h>
#include <stdint.h>
#include <optional>
#include <span>
#include "index_buffer.hpp"
#include "vertex_buffer.hpp"
#include "vertex_types.hpp"

namespace ember {

class VertexArray {
 public:
  template <Vertex T>
  VertexArray(std::span<T> vertices, std::optional<std::span<const uint32_t>> indices, GLenum usage)
      : m_vertexBuffer(vertices, usage) {
    if (indices) {
      m_indexBuffer = {*indices, usage};
    }

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    m_vertexBuffer.bind();
    if (m_indexBuffer) m_indexBuffer->bind();

    T::vertexAttrib();

    glBindVertexArray(0);

    if (m_indexBuffer) m_indexBuffer->unbind();
    m_vertexBuffer.unbind();

    if (indices)
      m_numVertices = indices->size();
    else
      m_numVertices = vertices.size();
  }

  virtual ~VertexArray();

  VertexArray(const VertexArray &) = delete;
  auto operator=(const VertexArray &) -> VertexArray & = delete;

  VertexArray(VertexArray &&);
  auto operator=(VertexArray &&) -> VertexArray &;

  inline auto bind() const { glBindVertexArray(m_VAO); }
  inline auto unbind() const { glBindVertexArray(0); }

  [[nodiscard]] inline auto getNumVertices() const { return m_numVertices; }
  [[nodiscard]] inline auto isIndexed() const { return m_indexBuffer.has_value(); }
  [[nodiscard]] virtual auto getPrimitiveType() const -> GLenum = 0;

 private:
  uint32_t m_VAO;
  VertexBuffer m_vertexBuffer;
  std::optional<IndexBuffer> m_indexBuffer;

  size_t m_numVertices;
};

}  // namespace ember

#endif  // VERTEX_ARRAY_HPP