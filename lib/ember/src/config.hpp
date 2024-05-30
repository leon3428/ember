#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <cstddef>

namespace ember::config {
// Has to be prime
constexpr size_t resourceIndexCapacity = 2003;
constexpr size_t resourceCacheCapacity = 2003;

constexpr const char *shaderFolder = "shaders";

}  // namespace ember::config

#endif  // CONFIG_HPP