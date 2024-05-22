#include "resource_descriptions.hpp"

namespace rd = ember::resource_desc;

template <>
auto rd::load<rd::Object>(const rapidjson::Value &value) -> rd::Object {
  return {value["name"].GetString(), value["path"].GetString()};
}