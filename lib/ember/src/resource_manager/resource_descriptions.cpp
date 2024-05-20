#include "resource_descriptions.hpp"

namespace rd = ember::resource_desc;

template <>
auto rd::load<rd::Mesh>(const rapidjson::Value &value) -> rd::Mesh {
  return {value["name"].GetString(), value["path"].GetString()};
}