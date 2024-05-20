#ifndef SHADER_PROGRAM_LOADER
#define SHADER_PROGRAM_LOADER

#include "../core/utils.hpp"
#include "shader_program.hpp"

namespace ember::shader_program {

[[nodiscard]] auto load(Identifier idn) -> ember::ShaderProgram;

}  // namespace ember::shader_program

#endif  // SHADER_PROGRAM_LOADER