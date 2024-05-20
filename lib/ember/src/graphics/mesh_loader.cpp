#include "mesh_loader.hpp"
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <glm/glm.hpp>
#include <vector>
#include "../resource_manager/resource_index.hpp"
#include "vertex_types.hpp"

auto ember::mesh::load(Identifier idn) -> ember::Mesh {
  auto description = getResourceIndex()->getDescription<resource_desc::Mesh>(idn);

  if (!description) throw("Mesh with that identifier does not exist");

  Assimp::Importer importer;

  // clang-format off
  auto scene = importer.ReadFile(
    description->path, 
    aiProcess_CalcTangentSpace | aiProcess_Triangulate |
    aiProcess_JoinIdenticalVertices | aiProcess_SortByPType |
    aiProcess_FlipUVs | aiProcess_GenNormals
  );
  // clang-format on

  if (nullptr == scene) {
    throw std::runtime_error(importer.GetErrorString());
  }

  if (scene->mNumMeshes < 1) throw std::runtime_error("File does not contain a mesh");
  auto mesh = scene->mMeshes[0];

  std::vector<PosVertex> vertices;
  std::vector<uint32_t> indices;

  float x_min = std::numeric_limits<float>::max();
  float x_max = -std::numeric_limits<float>::max();
  float y_min = std::numeric_limits<float>::max();
  float y_max = -std::numeric_limits<float>::max();
  float z_min = std::numeric_limits<float>::max();
  float z_max = -std::numeric_limits<float>::max();

  for (size_t i = 0; i < mesh->mNumVertices; i++) {
    auto vertex = mesh->mVertices[i];
    vertices.emplace_back(glm::vec3(vertex.x, vertex.y, vertex.z));

    x_min = std::min(x_min, vertex.x);
    x_max = std::max(x_max, vertex.x);

    y_min = std::min(y_min, vertex.y);
    y_max = std::max(y_max, vertex.y);

    z_min = std::min(z_min, vertex.z);
    z_max = std::max(z_max, vertex.z);
  }

  auto scale = 2.0f / std::max(std::max(x_max - x_min, y_max - y_min), z_max - z_min);
  glm::vec3 mean = {(x_max + x_min) / 2.0f, (y_max + y_min) / 2.0f, (z_max + z_min) / 2.0f};

  for (auto &v : vertices) {
    v.pos = (v.pos - mean) * scale;
  }

  for (size_t i = 0; i < mesh->mNumFaces; i++) {
    auto face = mesh->mFaces[i];
    for (size_t j = 0; j < face.mNumIndices; j++) {
      indices.push_back(face.mIndices[j]);
    }
  }

  return {std::span<PosVertex>{vertices}, indices};
}