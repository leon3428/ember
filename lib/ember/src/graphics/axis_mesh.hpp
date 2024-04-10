#ifndef AXIS_MESH_HPP
#define AXIS_MESH_HPP

#include <span>
#include <array>
#include "static_mesh.hpp"
#include "vertex_types.hpp"
#include "render_group.hpp"
#include "vertex_color_material.hpp"

namespace ember {


[[nodiscard]] inline auto getAxisRenderGroup() -> RenderGroup& {
  constexpr static std::array<PosColVertex, 6> axisVertices = {ember::PosColVertex({0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}),
                                            ember::PosColVertex({1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}),
                                            ember::PosColVertex({0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}),
                                            ember::PosColVertex({0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}),
                                            ember::PosColVertex({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}),
                                            ember::PosColVertex({0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f})};

  constexpr static std::array<uint32_t, 6> axisIndices = {0, 1, 2, 3, 4, 5};

  static StaticMesh mesh(std::span<const PosColVertex>{axisVertices}, axisIndices);
  static VertexColorMaterial material;
  static RenderGroup renderGroup = {&material, &mesh, mesh.getNumVertices(), 0};

  return renderGroup;
}

}  // namespace ember

#endif  // AXIS_MESH_HPP