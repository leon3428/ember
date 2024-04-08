#ifndef BASE_MESH_HPP
#define BASE_MESH_HPP

#include <span>

#include <glad/glad.h>

#include "vertex_types.hpp"

namespace ember {

class BaseMesh {
 public:
  template <Vertex T>
  BaseMesh(std::span<T> vertices, std::span<uint32_t> indices, GLenum usage) {
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size_bytes(), vertices.data(), usage);

    T::vertexAttrib();

    glGenBuffers(1, &m_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size_bytes(), indices.data(), usage);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    m_numVertices = indices.size();
  }

  // class is not copyable
  BaseMesh(const BaseMesh &) = delete;
  auto operator=(const BaseMesh &) -> BaseMesh & = delete;

  BaseMesh(BaseMesh &&other);
  auto operator=(BaseMesh &&other) -> BaseMesh &;

  [[nodiscard]] inline auto getNumVertices() const { return m_numVertices; }

 protected:
  ~BaseMesh();

  uint32_t m_VAO;
  uint32_t m_VBO;
  uint32_t m_EBO;

  size_t m_numVertices;
};

}  // namespace ember

#endif  // BASE_MESH_HPP