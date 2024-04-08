#ifndef SHADER_HPP
#define SHADER_HPP

#include <cstdint>
#include <string_view>
#include <filesystem>

namespace ember {

    class Shader {
        public:
            static constexpr unsigned errorMessageLength = 512;
            
            Shader(unsigned type, std::string_view source);
            ~Shader();

            Shader(const Shader&) = delete;
            auto operator=(const Shader&) -> Shader& = delete;
            
            Shader(Shader&&);
            auto operator=(Shader&&) -> Shader&;

            [[nodiscard]] inline auto getShaderId() const { return m_shaderId; }

        private:
            uint32_t m_shaderId;
    };

    auto makeShaderFromFile(unsigned type, std::filesystem::path path) -> Shader;

}

#endif // SHADER_HPP