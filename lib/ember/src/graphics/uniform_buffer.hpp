#ifndef UNIFORM_BUFFER_HPP
#define UNIFORM_BUFFER_HPP

#include <glad/glad.h>
#include <stdint.h>

namespace ember {
class UniformBuffer {
 public:
  template <typename  T>
  UniformBuffer(const T *data, unsigned binding, GLenum usage) {
    glGenBuffers(1, &m_UBO);
    glBindBuffer(GL_UNIFORM_BUFFER, m_UBO);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(T), data, usage);
    glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_UBO); 
  }
  ~UniformBuffer();

  UniformBuffer(const UniformBuffer &) = delete;
  auto operator=(const UniformBuffer &) -> UniformBuffer & = delete;

  UniformBuffer(UniformBuffer &&);
  auto operator=(UniformBuffer &&) -> UniformBuffer &;

  inline auto bind() const { glBindBuffer(GL_UNIFORM_BUFFER, m_UBO); };
  inline auto unbind() const { glBindBuffer(GL_UNIFORM_BUFFER, 0); };

 private:
  uint32_t m_UBO;
};
}  // namespace ember

#endif  // UNIFORM_BUFFER_HPP