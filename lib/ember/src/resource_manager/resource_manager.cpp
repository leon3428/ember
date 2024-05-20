#include "resource_manager.hpp"
#include "../config.hpp"
#include "../graphics/mesh_loader.hpp"
#include "../graphics/shader_program_loader.hpp"

ember::ResourceManager::ResourceManager() : m_resourceCache(config::resourceCacheCapacity) {}

auto ember::ResourceManager::getShaderProgram(Identifier idn) -> ShaderProgram * {
  auto pShaderProgram = m_resourceCache.get<ShaderProgram>(idn);

  if (pShaderProgram) return pShaderProgram;

  m_resourceCache.set<ShaderProgram>(idn, shader_program::load(idn));
  pShaderProgram = m_resourceCache.get<ShaderProgram>(idn);

  return pShaderProgram;
}

auto ember::ResourceManager::getMesh(Identifier idn) -> Mesh * {
  auto pMesh = m_resourceCache.get<Mesh>(idn);

  if (pMesh) return pMesh;

  m_resourceCache.set<Mesh>(idn, mesh::load(idn));
  pMesh = m_resourceCache.get<Mesh>(idn);

  return pMesh;
}
