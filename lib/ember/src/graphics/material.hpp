#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <glm/glm.hpp>
#include "shader_program.hpp"

namespace ember {

class Material {
 public:
  Material(const ShaderProgram *pShaderProgram);

  Material(const Material &) = default;
  auto operator=(const Material &) -> Material & = default;
  Material(Material &&) = default;
  auto operator=(Material &&) -> Material & = default;

  virtual ~Material() = default;

  virtual inline auto bind() const -> void { m_pShaderProgram->bind(); }

  virtual inline auto unbind() const -> void { m_pShaderProgram->unbind(); }

  virtual inline auto uploadUniforms() const -> void{};
  virtual inline auto uploadMvp(const glm::mat4 &, const glm::mat4 &, const glm::mat4 &) const -> void{};

 protected:
  const ShaderProgram *m_pShaderProgram;
};

}  // namespace ember

#endif  // MATERIAL_HPP