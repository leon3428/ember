#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include <glad/glad.h>
#include <span>

#include "shader.hpp"

namespace ember {

class ShaderProgram {
 public:
  static constexpr unsigned errorMessageLength = 512;

  ShaderProgram(std::span<Shader> shaders);

  ~ShaderProgram();

  ShaderProgram(const ShaderProgram &) = delete;
  auto operator=(const ShaderProgram &) -> ShaderProgram & = delete;

  ShaderProgram(ShaderProgram &&);
  auto operator=(ShaderProgram &&) -> ShaderProgram &;

  inline auto bind() const { glUseProgram(m_shaderProgramId); };
  inline auto unbind() const { glUseProgram(0); };

  // TODO: remove this
  [[nodiscard]] inline auto getShaderProgramId() const { return m_shaderProgramId; };

 private:
  uint32_t m_shaderProgramId;
};
}  // namespace ember

#endif  // SHADER_PROGRAM_HPP