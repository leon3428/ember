#include "vertex_array.hpp"

ember::VertexArray::~VertexArray() {
  if (m_VAO != 0) glDeleteVertexArrays(1, &m_VAO);
}

ember::VertexArray::VertexArray(VertexArray &&other)
    : m_vertexBuffer(std::move(other.m_vertexBuffer)), m_indexBuffer(std::move(other.m_indexBuffer)) {
  m_VAO = other.m_VAO;
  other.m_VAO = 0;

  m_numVertices = other.m_numVertices;
  other.m_numVertices = 0;
}

auto ember::VertexArray::operator=(VertexArray &&other) -> VertexArray & {
  if (this != &other) {
    m_vertexBuffer = std::move(other.m_vertexBuffer);
    m_indexBuffer = std::move(other.m_indexBuffer);

    if (m_VAO != 0) glDeleteVertexArrays(1, &m_VAO);

    m_VAO = other.m_VAO;
    other.m_VAO = 0;

    m_numVertices = other.m_numVertices;
    other.m_numVertices = 0;
  }

  return *this;
}
