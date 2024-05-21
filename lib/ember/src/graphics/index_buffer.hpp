#ifndef INDEX_BUFFER_HPP
#define INDEX_BUFFER_HPP

#include <glad/glad.h>
#include <stdint.h>
#include <span>

namespace ember {

class IndexBuffer {
 public:
  IndexBuffer(std::span<const uint32_t> indice, GLenum usages);
  ~IndexBuffer();

  IndexBuffer(const IndexBuffer &) = delete;
  auto operator=(const IndexBuffer &) -> IndexBuffer & = delete;

  IndexBuffer(IndexBuffer &&);
  auto operator=(IndexBuffer &&) -> IndexBuffer &;

  inline auto bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO); };
  inline auto unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); };

 private:
  uint32_t m_EBO;
};

}  // namespace ember

#endif  // INDEX_BUFFER_HPP