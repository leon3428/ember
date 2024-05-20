#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include "../core/conflict_free_variant_hash_map.hpp"
#include "../core/utils.hpp"
#include "../graphics/mesh.hpp"
#include "../graphics/shader_program.hpp"

namespace ember {

class ResourceManager {
 public:
  ResourceManager();

  [[nodiscard]] auto getShaderProgram(Identifier idn) -> ShaderProgram *;
  [[nodiscard]] auto getMesh(Identifier idn) -> Mesh *;

  inline auto moveMesh(Identifier idn, Mesh &&mesh) { m_resourceCache.set<Mesh>(idn, std::move(mesh)); }

  inline auto moveShaderProgram(Identifier idn, ShaderProgram &&shaderProgram) {
    m_resourceCache.set<ShaderProgram>(idn, std::move(shaderProgram));
  }

  inline auto clear() -> void { m_resourceCache.clear(); }

 private:
  ConflictFreeVariantHashMap<uint32_t, ShaderProgram, Mesh> m_resourceCache;
};

inline auto getResourceManager() -> ResourceManager * {
  static ResourceManager resourceManager;
  return &resourceManager;
}

}  // namespace ember

#endif  // RESOURCE_MANAGER_HPP