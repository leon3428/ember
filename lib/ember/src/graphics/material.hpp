#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <glm/glm.hpp>
#include "shader_program.hpp"
#include "texture.hpp"

namespace ember {

class Material {
 public:
  Material(const ShaderProgram *pShaderProgram);

  Material(const Material &) = default;
  auto operator=(const Material &) -> Material & = default;
  Material(Material &&) = default;
  auto operator=(Material &&) -> Material & = default;

  virtual ~Material() = default;

  inline auto bind() const -> void {
    m_pShaderProgram->bind();
    m_pTexture->bind();
  }

  inline auto unbind() const -> void {
    m_pShaderProgram->unbind();
    m_pTexture->unbind();
  }

  virtual inline auto uploadUniforms() const -> void{};
  virtual inline auto uploadMvp(const glm::mat4 &, const glm::mat4 &, const glm::mat4 &) const -> void{};

  inline auto setTexture(const Texture *pTexture) { m_pTexture = pTexture; }

 protected:
  const ShaderProgram *m_pShaderProgram;
  // TODO: more than one texture
  const Texture *m_pTexture;
};

}  // namespace ember

#endif  // MATERIAL_HPP