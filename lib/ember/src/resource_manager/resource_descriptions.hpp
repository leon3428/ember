#ifndef RESOURCE_DESCRIPTION_HPP
#define RESOURCE_DESCRIPTION_HPP

#include <rapidjson/document.h>
#include <filesystem>
#include <string>
#include "../core/utils.hpp"

namespace ember::resource_desc {

struct Object {
  ember::Identifier parent;
  std::string name;
  std::filesystem::path path;
};

enum class TextureType {
  Unknown,
  Diffuse,
  Normal
};

struct Texture {
  ember::Identifier parent;
  std::string name;
  TextureType textureType;
  std::filesystem::path path;
};

enum class CurveType {
  Unknown,
  CubicBSpline
};

struct Curve {
  ember::Identifier parent;
  std::string name;
  CurveType curveType;
  std::filesystem::path path;
};

template <typename T>
auto load(const rapidjson::Value &value) -> T;

template <>
auto load<Object>(const rapidjson::Value &value) -> Object;

template <>
auto load<Texture>(const rapidjson::Value &value) -> Texture;

template <>
auto load<Curve>(const rapidjson::Value &value) -> Curve;


}  // namespace ember::resource_desc

#endif  // RESOURCE_DESCRIPTION_HPP