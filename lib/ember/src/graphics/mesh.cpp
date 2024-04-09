#include "mesh.hpp"

ember::Mesh::~Mesh() {
  if (m_VAO != 0) glDeleteVertexArrays(1, &m_VAO);
  if (m_VBO != 0) glDeleteBuffers(1, &m_VBO);
  if (m_EBO != 0) glDeleteBuffers(1, &m_EBO);
}

ember::Mesh::Mesh(Mesh &&other) {
  m_VBO = other.m_VBO;
  other.m_VBO = 0;

  m_EBO = other.m_EBO;
  other.m_EBO = 0;

  m_VAO = other.m_VAO;
  other.m_VAO = 0;
}

auto ember::Mesh::operator=(Mesh &&other) -> ember::Mesh & {
  if (this != &other) {
    if (m_VBO != 0) glDeleteBuffers(1, &m_VBO);

    m_VBO = other.m_VBO;
    other.m_VBO = 0;

    if (m_EBO != 0) glDeleteBuffers(1, &m_EBO);

    m_EBO = other.m_EBO;
    other.m_EBO = 0;

    if (m_VAO != 0) glDeleteVertexArrays(1, &m_VAO);

    m_VAO = other.m_VAO;
    other.m_VAO = 0;
  }

  return *this;
}
