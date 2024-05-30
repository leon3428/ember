#include "shader_program.hpp"

#include <glad/glad.h>
#include <cstdint>
#include <format>

ember::ShaderProgram::ShaderProgram(std::span<Shader> shaders, uint32_t emberId)
    : m_shaderProgramId(glCreateProgram()), m_emberId(emberId) {
  for (const auto &shader : shaders) {
    glAttachShader(m_shaderProgramId, shader.getShaderId());
  }

  glLinkProgram(m_shaderProgramId);
  glValidateProgram(m_shaderProgramId);

  int success;
  glGetProgramiv(m_shaderProgramId, GL_LINK_STATUS, &success);

  if (!success) {
    char infoLog[errorMessageLength];
    glGetProgramInfoLog(m_shaderProgramId, errorMessageLength, NULL, infoLog);

    glDeleteProgram(m_shaderProgramId);
    m_shaderProgramId = 0;

    throw std::runtime_error(std::format("Failed to link program:\n{}", infoLog));
  }
}

ember::ShaderProgram::~ShaderProgram() {
  if (m_shaderProgramId != 0) glDeleteProgram(m_shaderProgramId);
}

ember::ShaderProgram::ShaderProgram(ShaderProgram &&other) {
  m_shaderProgramId = other.m_shaderProgramId;
  m_emberId = other.m_emberId;
  other.m_shaderProgramId = 0;
  other.m_emberId = 0;
}

auto ember::ShaderProgram::operator=(ShaderProgram &&other) -> ShaderProgram & {
  if (this != &other) {
    if (m_shaderProgramId != 0) glDeleteProgram(m_shaderProgramId);

    m_shaderProgramId = other.m_shaderProgramId;
    m_emberId = other.m_emberId;
    other.m_shaderProgramId = 0;
    other.m_emberId = 0;
  }

  return *this;
}
