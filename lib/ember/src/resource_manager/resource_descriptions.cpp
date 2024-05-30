#include "resource_descriptions.hpp"

namespace rd = ember::resource_desc;

template <>
auto rd::load<rd::Object>(const rapidjson::Value &value) -> rd::Object {
  Identifier parent = {0};
  if(value["parent"].IsString())
    parent = hash(value["parent"].GetString());

  return { parent, value["name"].GetString(), value["path"].GetString()};
}

template <>
auto rd::load<rd::Texture>(const rapidjson::Value &value) -> rd::Texture {
  Identifier parent = {0};
  if(value["parent"].IsString())
    parent = hash(value["parent"].GetString());

  auto textureType = TextureType::Unknown;
  if(value["textureType"].IsString()) {
    auto tt  = value["textureType"].GetString();
    if(strcmp(tt, "diffuse") == 0)
      textureType = TextureType::Diffuse;
  }

  return { parent, value["name"].GetString(), textureType, value["path"].GetString()};
}