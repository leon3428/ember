#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <glm/glm.hpp>
#include "shader_program.hpp"

namespace ember {

class Material {
 public:
  inline auto bindProgram() const -> void { m_shaderProgram.bind(); }
  virtual inline auto uploadUniforms() const -> void{};
  virtual inline auto uploadMvp(const glm::mat4 &) const -> void{};

 protected:
  Material(const ShaderProgram *shaderProgram);

  Material(const Material &) = default;
  auto operator=(const Material &) -> Material & = delete;

  Material(Material &&) = default;
  auto operator=(Material &&) -> Material & = delete;

  ~Material() = default;

  const ShaderProgram &m_shaderProgram;
};

}  // namespace ember

#endif  // MATERIAL_HPP