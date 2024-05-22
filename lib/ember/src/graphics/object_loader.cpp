#include "object_loader.hpp"
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include "../resource_manager/resource_index.hpp"
#include "../resource_manager/resource_manager.hpp"
#include "mesh.hpp"
#include "phong_material.hpp"
#include "renderable.hpp"
#include "vertex_types.hpp"

auto ember::loadObject(Identifier idn) -> ember::Node {
  auto description = getResourceIndex()->getDescription<resource_desc::Object>(idn);

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

  auto pResourceManager = getResourceManager();

  if (scene->mNumMeshes < 1) throw std::runtime_error("File does not contain a mesh");
  auto mesh = scene->mMeshes[0];
  auto meshNameHash = hash(mesh->mName.C_Str());
  auto pEmberMesh = pResourceManager->getMesh(meshNameHash);
  if (!pEmberMesh) {
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

    Mesh emberMesh(std::span<PosVertex>{vertices}, indices);
    pResourceManager->moveMesh(meshNameHash, std::move(emberMesh));
    pEmberMesh = pResourceManager->getMesh(meshNameHash);
  }

  Node root;
  auto pRenderable = root.emplaceChild<Renderable>();
  pRenderable->pVertexArray = pEmberMesh;
  pRenderable->byteOffset = 0;
  pRenderable->vertexCnt = pEmberMesh->getNumVertices();

  if (scene->mNumMaterials > 1) {
    auto pMaterial = scene->mMaterials[1];
    std::cout << pMaterial->GetName().C_Str() << '\n';
    auto materialNameHash = hash(pMaterial->GetName().C_Str());
    auto pCachedMaterial = pResourceManager->getMaterial(materialNameHash);
    if (!pCachedMaterial) {
      auto pEmberMaterial = std::make_unique<PhongMaterial>();

      aiColor3D ambientK, diffuseK, specularK;
      float shininessK;

      pMaterial->Get(AI_MATKEY_COLOR_AMBIENT, ambientK);
      pMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseK);
      pMaterial->Get(AI_MATKEY_COLOR_SPECULAR, specularK);
      pMaterial->Get(AI_MATKEY_SHININESS, shininessK);

      pEmberMaterial->ambientColor.r = ambientK.r;
      pEmberMaterial->ambientColor.g = ambientK.g;
      pEmberMaterial->ambientColor.b = ambientK.b;

      pEmberMaterial->diffuseColor.r = diffuseK.r;
      pEmberMaterial->diffuseColor.g = diffuseK.g;
      pEmberMaterial->diffuseColor.b = diffuseK.b;

      pEmberMaterial->specularColor.r = specularK.r;
      pEmberMaterial->specularColor.g = specularK.g;
      pEmberMaterial->specularColor.b = specularK.b;

      pEmberMaterial->shininess = shininessK;

      pCachedMaterial = pEmberMaterial.get();
      pResourceManager->moveMaterial(materialNameHash, std::move(pEmberMaterial));
    }

    pRenderable->pMaterial = pCachedMaterial;
  }

  return root;
}