#include "shader.hpp"

#include <format>
#include <glad/glad.h>
#include "../core/utils.hpp"

ember::Shader::Shader(unsigned type, std::string_view source)
    : m_shaderId(glCreateShader(type))
{
	auto src = source.data();
	glShaderSource(m_shaderId, 1, &src, nullptr);
	glCompileShader(m_shaderId);

	int success;
	glGetShaderiv(m_shaderId, GL_COMPILE_STATUS, &success);

	if(!success) {
		char infoLog[errorMessageLength];
		glGetShaderInfoLog(m_shaderId, errorMessageLength, NULL, infoLog);
        
        glDeleteShader(m_shaderId);
        m_shaderId = 0;

        throw std::runtime_error(std::format("Failed to compile {} shader:\n{}", (type == GL_VERTEX_SHADER ? "vertex" : "fragment"), infoLog));
	}
}

ember::Shader::~Shader() {
    if(m_shaderId != 0)
        glDeleteShader(m_shaderId);
}

ember::Shader::Shader(Shader&& other) {
    m_shaderId = other.m_shaderId;
    other.m_shaderId = 0;
}

auto ember::Shader::operator=(Shader&& other) -> Shader& {
    if(this != &other) {
        if(m_shaderId != 0)
            glDeleteShader(m_shaderId);

        m_shaderId = other.m_shaderId;
        other.m_shaderId = 0;
    }

    return *this;
}

auto ember::makeShaderFromFile(unsigned type, std::filesystem::path path) -> Shader {
    auto shaderSource = readFile(path);

    if(shaderSource) {
        return Shader(type, *shaderSource);
    }

    throw std::runtime_error(std::format("File {} does not exist", path.c_str()));
}