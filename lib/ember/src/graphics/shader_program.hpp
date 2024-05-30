#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include <glad/glad.h>
#include <cstdint>
#include <span>

#include "index_buffer.hpp"
#include "shader.hpp"

namespace ember {

class ShaderProgram {
 public:
  static constexpr unsigned errorMessageLength = 512;

  ShaderProgram(std::span<Shader> shaders, uint32_t emberId);

  ~ShaderProgram();

  ShaderProgram(const ShaderProgram &) = delete;
  auto operator=(const ShaderProgram &) -> ShaderProgram & = delete;

  ShaderProgram(ShaderProgram &&);
  auto operator=(ShaderProgram &&) -> ShaderProgram &;

  inline auto bind() const { glUseProgram(m_shaderProgramId); };
  inline auto unbind() const { glUseProgram(0); };

  [[nodiscard]] inline auto getShaderProgramId() const { return m_shaderProgramId; };
  [[nodiscard]] inline auto getEmberId() const { return m_emberId; }

 private:
  uint32_t m_shaderProgramId;
  uint32_t m_emberId;
};
}  // namespace ember

#endif  // SHADER_PROGRAM_HPP