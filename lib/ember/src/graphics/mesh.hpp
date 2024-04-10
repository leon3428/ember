#ifndef MESH_HPP
#define MESH_HPP

#include <glad/glad.h>
#include <span>

#include "vertex_types.hpp"

namespace ember {

class Mesh {
 public:
  [[nodiscard]] inline auto getNumVertices() const { return m_numVertices; }

  inline auto bind() const { glBindVertexArray(m_VAO); }
  inline auto unbind() const { glBindVertexArray(0); }

 protected:
 
  template <Vertex T>
  Mesh(std::span<T> vertices, std::span<const uint32_t> indices, GLenum usage) {
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
  Mesh(const Mesh &) = delete;
  auto operator=(const Mesh &) -> Mesh & = delete;

  Mesh(Mesh &&other);
  auto operator=(Mesh &&other) -> Mesh &;
  
  ~Mesh();

  uint32_t m_VAO;
  uint32_t m_VBO;
  uint32_t m_EBO;

  size_t m_numVertices;
};

}  // namespace ember

#endif  // MESH_HPP