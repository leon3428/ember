#ifndef DYNAMIC_MESH_HPP
#define DYNAMIC_MESH_HPP

#include "base_mesh.hpp"

namespace ember {

// TODO: This class is incomplete
template <Vertex T>
class DynamicMesh : public BaseMesh {
 public:
  DynamicMesh(size_t maxVertices, size_t maxIndices)
      : BaseMesh(std::span<T>(foo, maxVertices), std::span<uint32_t>(bar, maxIndices), GL_DYNAMIC_DRAW) {
    m_numVertices = 0;
  }

  auto writeVertex(size_t i, const T &vertex) {
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    // potential alignment issues
    glBufferSubData(GL_ARRAY_BUFFER, i * sizeof(T), sizeof(T), &vertex);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  auto writeIndex(size_t i, uint32_t index) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, i * sizeof(uint32_t), sizeof(uint32_t), &index);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  // TODO: remove this
  inline auto bind() const { glBindVertexArray(m_VAO); }

  // TODO: remove this
  inline auto unbind() const { glBindVertexArray(0); }

 private:
  // TODO: this is a bit hacky
  static constexpr T *foo = nullptr;
  static constexpr uint32_t *bar = nullptr;
};

}  // namespace ember

#endif  // DYNAMIC_MESH_HPP