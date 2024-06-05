#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <glad/glad.h>
#include <stdint.h>
#include "../core/image.hpp"

namespace ember {

struct TextureDesc {
  int width;
  int height;
  int internalFormat;
  int format;
  int type;
  int minFilter;
  int magFilter;
  bool genMipMap;
};

class Texture {
 public:
  Texture(const Image &image);
  Texture(const TextureDesc &textureDesc, const unsigned char *data);
  ~Texture();

  Texture(const Texture &) = delete;
  auto operator=(const Texture &) -> Texture & = delete;

  Texture(Texture &&);
  auto operator=(Texture &&) -> Texture &;

  inline auto bind() const {
    glBindTexture(GL_TEXTURE_2D, m_textureId);
  };

  inline auto unbind() const { glBindTexture(GL_TEXTURE_2D, 0); };
  [[nodiscard]] inline auto getTextureId() const { return m_textureId; }

 private:
  uint32_t m_textureId;
};

}  // namespace ember

#endif  // TEXTURE_HPP