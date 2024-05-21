#include "index_buffer.hpp"

ember::IndexBuffer::IndexBuffer(std::span<const uint32_t> indices, GLenum usage) {
  glGenBuffers(1, &m_EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size_bytes(), indices.data(), usage);
}

ember::IndexBuffer::~IndexBuffer() {
  if (m_EBO != 0) glDeleteBuffers(1, &m_EBO);
}

ember::IndexBuffer::IndexBuffer(IndexBuffer &&other) {
  m_EBO = other.m_EBO;
  other.m_EBO = 0;
}

auto ember::IndexBuffer::operator=(IndexBuffer &&other) -> IndexBuffer & {
  if (this != &other) {
    if (m_EBO != 0) glDeleteBuffers(1, &m_EBO);

    m_EBO = other.m_EBO;
    other.m_EBO = 0;
  }

  return *this;
}
