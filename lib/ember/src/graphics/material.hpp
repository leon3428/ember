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

  virtual inline auto bindProgram() const -> void { m_pShaderProgram->bind(); }
  virtual inline auto unbindProgram() const -> void { m_pShaderProgram->unbind(); }
  virtual inline auto uploadUniforms(const glm::mat4 &transform, const glm::mat4 &transformInv, const glm::mat4 &p) const -> void = 0;
  [[nodiscard]] inline auto getShaderProgramId() const  { return m_pShaderProgram->getShaderProgramId(); }
  [[nodiscard]] inline auto getEmberId() const  { return m_pShaderProgram->getEmberId(); }

 protected:
  const ShaderProgram *m_pShaderProgram;
};

}  // namespace ember

#endif  // MATERIAL_HPP