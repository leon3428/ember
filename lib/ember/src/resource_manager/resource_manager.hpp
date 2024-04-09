#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include "../core/conflict_free_variant_hash_map.hpp"
#include "../core/utils.hpp"
#include "../graphics/shader_program.hpp"
#include "resource_map.hpp"
#include "../graphics/static_mesh.hpp"

namespace ember {

class ResourceManager {
 public:
  ResourceManager();

  [[nodiscard]] auto getShaderProgram(Identifier idn) -> ShaderProgram *;
  [[nodiscard]] auto getStaticMesh(Identifier idn) -> StaticMesh *;
  [[nodiscard]] inline auto getResourceMap() -> ResourceMap & { return m_resourceMap; }

  inline auto clear() -> void { m_resourceCache.clear(); }

 private:
  ResourceMap m_resourceMap;
  ConflictFreeVariantHashMap<uint32_t, ShaderProgram, StaticMesh> m_resourceCache;
};

inline auto getResourceManager() -> ResourceManager& {
  static ResourceManager resourceManager;
  return resourceManager;
}

}  // namespace ember

#endif  // RESOURCE_MANAGER_HPP