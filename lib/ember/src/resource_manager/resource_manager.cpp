#include "resource_manager.hpp"
#include "../graphics/shader_program_loader.hpp"
#include "../graphics/texture_loader.hpp"

auto ember::ResourceManager::getShaderProgram(Identifier idn) -> ShaderProgram * {
  auto pShaderProgram = m_resourceCache.get<ShaderProgram>(idn);

  if (pShaderProgram) return pShaderProgram;

  m_resourceCache.set<ShaderProgram>(idn, shader_program::load(idn));
  pShaderProgram = m_resourceCache.get<ShaderProgram>(idn);

  return pShaderProgram;
}

// TODO: implement cache
auto ember::ResourceManager::getMesh(Identifier idn) -> Mesh * {
  auto pMesh = m_resourceCache.get<Mesh>(idn);

  return pMesh;
}

// implement cache
auto ember::ResourceManager::getMaterial(Identifier idn) -> Material * {
  auto p = m_resourceCache.get<std::unique_ptr<Material>>(idn);
  if (p) return p->get();
  return nullptr;
}

auto ember::ResourceManager::getTexture(Identifier idn) -> Texture * {
  auto pTexture = m_resourceCache.get<Texture>(idn);

  if (pTexture) return pTexture;

  m_resourceCache.set<Texture>(idn, texture::load(idn));
  pTexture = m_resourceCache.get<Texture>(idn);

  return pTexture;
}