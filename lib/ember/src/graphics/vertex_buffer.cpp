#include "vertex_buffer.hpp"

ember::VertexBuffer::~VertexBuffer() {
  if (m_VBO != 0) glDeleteBuffers(1, &m_VBO);
}

ember::VertexBuffer::VertexBuffer(VertexBuffer &&other) {
  m_VBO = other.m_VBO;
  other.m_VBO = 0;
}

auto ember::VertexBuffer::operator=(VertexBuffer &&other) -> VertexBuffer & {
  if (this != &other) {
    if (m_VBO != 0) glDeleteBuffers(1, &m_VBO);

    m_VBO = other.m_VBO;
    other.m_VBO = 0;
  }

  return *this;
}
