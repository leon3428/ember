#include "uniform_buffer.hpp"

ember::UniformBuffer::~UniformBuffer() {
  if (m_UBO != 0) glDeleteBuffers(1, &m_UBO);
}

ember::UniformBuffer::UniformBuffer(UniformBuffer &&other) {
  m_UBO = other.m_UBO;
  other.m_UBO = 0;
}

auto ember::UniformBuffer::operator=(UniformBuffer &&other) -> UniformBuffer & {
  if (this != &other) {
    if (m_UBO != 0) glDeleteBuffers(1, &m_UBO);

    m_UBO = other.m_UBO;
    other.m_UBO = 0;
  }

  return *this;
}
