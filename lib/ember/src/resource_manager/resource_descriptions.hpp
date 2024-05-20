#ifndef RESOURCE_DESCRIPTION_HPP
#define RESOURCE_DESCRIPTION_HPP

#include <rapidjson/document.h>
#include <filesystem>
#include <string>

namespace ember::resource_desc {

struct Mesh {
  std::string name;
  std::filesystem::path path;
};

template <typename T>
auto load(const rapidjson::Value &value) -> T;

template <>
auto load<Mesh>(const rapidjson::Value &value) -> Mesh;

}  // namespace ember::resource_desc

#endif  // RESOURCE_DESCRIPTION_HPP