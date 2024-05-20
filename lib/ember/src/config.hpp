#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <cstddef>

namespace ember::config {
// Has to be prime
constexpr size_t resourceIndexCapacity = 1009;
constexpr size_t resourceCacheCapacity = 1009;

constexpr const char *shaderFolder = "shaders";

}  // namespace ember::config

#endif  // CONFIG_HPP