#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

#include <cstddef>

#include <glm/glm.hpp>

#include "material.hpp"
#include "mesh.hpp"
#include "object3d.hpp"

namespace ember {

class Renderable : public Object3d {
 public:
  Renderable();

  Material *pMaterial;
  Mesh *pMesh;
  size_t vertexCnt;
  size_t byteOffset;
};

}  // namespace ember

#endif  // RENDERABLE_HPP