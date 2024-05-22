#ifndef RESOURCE_DESCRIPTION_HPP
#define RESOURCE_DESCRIPTION_HPP

#include <rapidjson/document.h>
#include <filesystem>
#include <string>

namespace ember::resource_desc {

struct Object {
  std::string name;
  std::filesystem::path path;
};

template <typename T>
auto load(const rapidjson::Value &value) -> T;

template <>
auto load<Object>(const rapidjson::Value &value) -> Object;

}  // namespace ember::resource_desc

#endif  // RESOURCE_DESCRIPTION_HPP