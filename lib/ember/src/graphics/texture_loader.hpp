#ifndef TEXTURE_LOADER_HPP
#define TEXTURE_LOADER_HPP

#include "../core/utils.hpp"
#include "texture.hpp"

namespace ember::texture {

[[nodiscard]] auto load(Identifier idn) -> ember::Texture;

}

#endif  // TEXTURE_LOADER_HPP