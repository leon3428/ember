#include "resource_manager.hpp"
#include "../config.hpp"
#include "../graphics/shader_program_loader.hpp"
#include "../graphics/mesh_loader.hpp"

ember::ResourceManager::ResourceManager() : m_resourceCache(config::resourceCacheCapacity) {}

auto ember::ResourceManager::getShaderProgram(Identifier idn) -> ShaderProgram * {
  auto pShaderProgram = m_resourceCache.get<ShaderProgram>(idn);

  if (pShaderProgram) return pShaderProgram;

  m_resourceCache.set<ShaderProgram>(idn, shader_program::load(idn, m_resourceMap));
  pShaderProgram = m_resourceCache.get<ShaderProgram>(idn);

  return pShaderProgram;
}

auto ember::ResourceManager::getStaticMesh(Identifier idn) -> StaticMesh * {
  auto pStaticMesh = m_resourceCache.get<StaticMesh>(idn);

  if (pStaticMesh) return pStaticMesh;

  m_resourceCache.set<StaticMesh>(idn, static_mesh::load(idn, m_resourceMap));
  pStaticMesh = m_resourceCache.get<StaticMesh>(idn);

  return pStaticMesh;
}
