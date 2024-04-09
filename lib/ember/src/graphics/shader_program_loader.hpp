#ifndef SHADER_PROGRAM_LOADER
#define SHADER_PROGRAM_LOADER

#include "shader_program.hpp"
#include "../core/utils.hpp"
#include "../resource_manager/resource_map.hpp"

namespace ember::shader_program {

[[nodiscard]] auto load(Identifier idn, const ResourceMap &resourceMap) -> ember::ShaderProgram;

}  // namespace ember

#endif  // SHADER_PROGRAM_LOADER