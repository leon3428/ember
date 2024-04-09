#ifndef RENDER_GROUP_HPP
#define RENDER_GROUP_HPP

#include <cstddef>

#include <glm/glm.hpp>

#include "material.hpp"
#include "mesh.hpp"

namespace ember {

struct RenderGroup {
  Material *pMaterial;
  Mesh *pMesh;
  size_t vertexCnt;
  size_t byteOffset;
};

}  // namespace ember

#endif  // RENDER_GROUP_HPP