#include "texture_loader.hpp"
#include "../core/image.hpp"
#include "../resource_manager/resource_index.hpp"
#include "stbimage/stb_image.hpp"

auto ember::texture::load(Identifier idn) -> ember::Texture {
  auto pResourceIndex = getResourceIndex();
  auto textureDesc = pResourceIndex->getDescription<resource_desc::Texture>(idn);

  Image image(textureDesc->path);
  Texture texture(image);

  return texture;
}