#include "resource_map.hpp"

auto ember::ResourceMap::getPath(Identifier name) const -> std::optional<std::filesystem::path> {
  if (m_resourceMap.contains(name)) {
    return m_resourceMap.at(name);
  }

  return {};
}
