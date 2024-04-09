#ifndef RESOURCE_MAP_HPP
#define RESOURCE_MAP_HPP

#include <filesystem>
#include <optional>
#include <unordered_map>
#include "../core/utils.hpp"

namespace ember {
class ResourceMap {
 public:
  inline auto addNamedResource(Identifier name, std::filesystem::path path) -> void { m_resourceMap[name] = path; }
  inline auto removeNamedResource(Identifier name) -> void { m_resourceMap.erase(name); }
  [[nodiscard]] auto getPath(Identifier name) const -> std::optional<std::filesystem::path>;

 private:
  std::unordered_map<Identifier, std::filesystem::path, IdentifierHash> m_resourceMap;
};
}  // namespace ember

#endif  // RESOURCE_MAP_HPP