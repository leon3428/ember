#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <glad/glad.h>
#include <stdint.h>
#include "../core/image.hpp"

namespace ember {

class Texture {
public:
  Texture(const Image &image);
  Texture(int width, int height, const unsigned char* data);
  ~Texture();

  Texture(const Texture&) = delete;
  auto operator=(const Texture&) -> Texture& = delete;

  Texture(Texture&&);
  auto operator=(Texture&&) -> Texture&;

  inline auto bind() const { glBindTexture(GL_TEXTURE_2D, m_textureId); };
  inline auto unbind() const { glBindTexture(GL_TEXTURE_2D, 0); };

private:
  uint32_t m_textureId;
};

}

#endif // TEXTURE_HPP