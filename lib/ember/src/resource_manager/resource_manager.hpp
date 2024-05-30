#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <memory>
#include "../core/variant_hash_map.hpp"
#include "../core/utils.hpp"
#include "../graphics/material.hpp"
#include "../graphics/mesh.hpp"
#include "../graphics/texture.hpp"
#include "../graphics/shader_program.hpp"

namespace ember {

class ResourceManager {
 public:
  [[nodiscard]] auto getShaderProgram(Identifier idn) -> ShaderProgram *;
  inline auto moveShaderProgram(Identifier idn, ShaderProgram &&shaderProgram) -> void {
    m_resourceCache.set<ShaderProgram>(idn, std::move(shaderProgram));
  }

  [[nodiscard]] auto getMesh(Identifier idn) -> Mesh *;
  inline auto moveMesh(Identifier idn, Mesh &&mesh) -> Mesh * {
    m_resourceCache.set<Mesh>(idn, std::move(mesh));
    return m_resourceCache.get<Mesh>(idn);
  }

  [[nodiscard]] auto getMaterial(Identifier idn) -> Material *;
  inline auto moveMaterial(Identifier idn, std::unique_ptr<Material> &&material) -> void {
    m_resourceCache.set<std::unique_ptr<Material>>(idn, std::move(material));
  }

  [[nodiscard]] auto getTexture(Identifier idn) -> Texture *;
  inline auto moveTexture(Identifier idn, Texture &&texture) -> void{
    m_resourceCache.set<Texture>(idn, std::move(texture));
  }

  inline auto clear() -> void { m_resourceCache.clear(); }

 private:
  VariantHashMap<Identifier, IdentifierHash, ShaderProgram, Mesh, Texture, std::unique_ptr<Material>> m_resourceCache;
};

inline auto getResourceManager() -> ResourceManager * {
  static ResourceManager resourceManager;
  return &resourceManager;
}

}  // namespace ember

#endif  // RESOURCE_MANAGER_HPP