#include "resource_manager.hpp"
#include "../config.hpp"
#include "../graphics/shader_program_loader.hpp"

ember::ResourceManager::ResourceManager() : m_resourceCache(config::resourceCacheCapacity) {}

auto ember::ResourceManager::getShaderProgram(Identifier idn) -> ShaderProgram * { 
  auto pShaderProgram = m_resourceCache.get<ShaderProgram>(idn);

  if(pShaderProgram)
    return pShaderProgram;

  m_resourceCache.set<ShaderProgram>(idn, shader_program::load(idn, m_resourceMap));
  pShaderProgram = m_resourceCache.get<ShaderProgram>(idn);

  return pShaderProgram;
}
