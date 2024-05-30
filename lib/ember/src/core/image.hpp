#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <filesystem>
namespace ember {

class Image {
 public:
  Image();
  Image(std::filesystem::path path);
  ~Image();

  Image(const Image &) = delete;
  auto operator=(const Image &) -> Image & = delete;

  Image(Image &&);
  auto operator=(Image &&) -> Image &;

  auto load(std::filesystem::path path) -> void;

  [[nodiscard]] inline auto getWidth() const { return m_width; }
  [[nodiscard]] inline auto getHeight() const { return m_height; }
  [[nodiscard]] inline auto getNumChannels() const { return m_numChannels; }
  [[nodiscard]] inline auto getDataPtr() const -> const unsigned char * { return m_pData; }

 private:
  int m_width;
  int m_height;
  int m_numChannels;
  unsigned char *m_pData;
};

}  // namespace ember

#endif  // IMAGE_HPP