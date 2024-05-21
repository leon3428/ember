#ifndef VERTEX_BUFFER_HPP
#define VERTEX_BUFFER_HPP

#include <glad/glad.h>
#include <stdint.h>
#include <span>
#include "vertex_types.hpp"

namespace ember {
class VertexBuffer {
 public:
  template <Vertex T>
  VertexBuffer(std::span<T> vertices, GLenum usage) {
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size_bytes(), vertices.data(), usage);
  }
  ~VertexBuffer();

  VertexBuffer(const VertexBuffer &) = delete;
  auto operator=(const VertexBuffer &) -> VertexBuffer & = delete;

  VertexBuffer(VertexBuffer &&);
  auto operator=(VertexBuffer &&) -> VertexBuffer &;

  inline auto bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_VBO); };
  inline auto unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); };

 private:
  uint32_t m_VBO;
};
}  // namespace ember

#endif  // VERTEX_BUFFER_HPP