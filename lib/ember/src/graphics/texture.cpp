#include "texture.hpp"

ember::Texture::Texture(const Image& image): ember::Texture::Texture(image.getWidth(), image.getHeight(), image.getDataPtr()) {}

ember::Texture::Texture(int width, int height, const unsigned char* data) {
  glGenTextures(1, &m_textureId);
  glBindTexture(GL_TEXTURE_2D, m_textureId);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
  glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
  glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
               data);
  glGenerateMipmap(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D, 0);
}

ember::Texture::~Texture() {
  if (m_textureId != 0) glDeleteTextures(1, &m_textureId);
}

ember::Texture::Texture(Texture &&other) {
  m_textureId = other.m_textureId;
  other.m_textureId = 0;
}

auto ember::Texture::operator=(Texture &&other) -> Texture & {
  if (this != &other) {
    if (m_textureId != 0) glDeleteTextures(1, &m_textureId);

    m_textureId = other.m_textureId;
    other.m_textureId = 0;
  }

  return *this;
}
