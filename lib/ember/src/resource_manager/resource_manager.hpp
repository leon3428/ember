#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <memory>
#include "../core/conflict_free_variant_hash_map.hpp"
#include "../core/utils.hpp"
#include "../graphics/material.hpp"
#include "../graphics/mesh.hpp"
#include "../graphics/shader_program.hpp"

namespace ember {

class ResourceManager {
 public:
  ResourceManager();

  [[nodiscard]] auto getShaderProgram(Identifier idn) -> ShaderProgram *;
  inline auto moveShaderProgram(Identifier idn, ShaderProgram &&shaderProgram) -> ShaderProgram * {
    m_resourceCache.set<ShaderProgram>(idn, std::move(shaderProgram));
    return m_resourceCache.get<ShaderProgram>(idn);
  }

  [[nodiscard]] auto getMesh(Identifier idn) -> Mesh *;
  inline auto moveMesh(Identifier idn, Mesh &&mesh) -> Mesh * {
    m_resourceCache.set<Mesh>(idn, std::move(mesh));
    return m_resourceCache.get<Mesh>(idn);
  }

  [[nodiscard]] inline auto getMaterial(Identifier idn) -> Material * {
    auto p = m_resourceCache.get<std::unique_ptr<Material>>(idn);
    if (p) return p->get();
    return nullptr;
  }
  inline auto moveMaterial(Identifier idn, std::unique_ptr<Material> &&material) -> Material * {
    m_resourceCache.set<std::unique_ptr<Material>>(idn, std::move(material));
    return m_resourceCache.get<std::unique_ptr<Material>>(idn)->get();
  }

  inline auto clear() -> void { m_resourceCache.clear(); }

 private:
  ConflictFreeVariantHashMap<uint32_t, ShaderProgram, Mesh, std::unique_ptr<Material>> m_resourceCache;
};

inline auto getResourceManager() -> ResourceManager * {
  static ResourceManager resourceManager;
  return &resourceManager;
}

}  // namespace ember

#endif  // RESOURCE_MANAGER_HPP