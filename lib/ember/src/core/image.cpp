#include "image.hpp"
#include <stdexcept>
#include "stbimage/stb_image.hpp"
#include <format>

ember::Image::Image() : m_width(0), m_height(0), m_numChannels(0), m_pData(nullptr) {}
ember::Image::Image(std::filesystem::path path) : m_pData(nullptr) { load(path); }

ember::Image::~Image() {
  if (m_pData) stbi_image_free(m_pData);
}

ember::Image::Image(Image &&other) {
  m_width = other.m_width;
  m_height = other.m_height;
  m_numChannels = other.m_numChannels;
  m_pData = other.m_pData;

  other.m_width = 0;
  other.m_height = 0;
  other.m_numChannels = 0;
  other.m_pData = nullptr;
}

auto ember::Image::operator=(Image &&other) -> Image & {
  if (this != &other) {
    if (m_pData) stbi_image_free(m_pData);

    m_width = other.m_width;
    m_height = other.m_height;
    m_numChannels = other.m_numChannels;
    m_pData = other.m_pData;

    other.m_width = 0;
    other.m_height = 0;
    other.m_numChannels = 0;
    other.m_pData = nullptr;
  }

  return *this;
}

auto ember::Image::load(std::filesystem::path path) -> void {
  if (m_pData) stbi_image_free(m_pData);
  m_pData = stbi_load(path.c_str(), &m_width, &m_height, &m_numChannels, 0);
  if(!m_pData)
    throw std::runtime_error(std::format("Failed to load image: {}", path.c_str()));
}