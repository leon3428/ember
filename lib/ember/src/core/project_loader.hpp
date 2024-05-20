#ifndef PROJECT_LOADER_HPP
#define PROJECT_LOADER_HPP

#include <filesystem>

namespace ember::project {

auto load(std::filesystem::path path) -> void;

}  // namespace ember::project

#endif  // PROJECT_LOADER_HPP