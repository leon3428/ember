#include "object_loader.hpp"
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <cstddef>
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

  if (scene == nullptr) {
    throw std::runtime_error(importer.GetErrorString());
  }

  auto pResourceManager = getResourceManager();
  Node root;

  // load materials
  for (size_t i = 0; i < scene->mNumMaterials; i++) {
    auto pMaterial = scene->mMaterials[i];

    std::string materialName = "EmberMaterial_";
    materialName += pMaterial->GetName().C_Str();

    std::cout << "Loading Material: " << materialName << '\n';
    auto materialNameHash = hash(materialName.c_str());

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
  }

  for (size_t meshInd = 0; meshInd < 8; meshInd++) {
    auto pMesh = scene->mMeshes[meshInd];

    std::string meshName = "EmberMesh_";
    meshName += pMesh->mName.C_Str();

    std::cout << "Loading Mesh: " << meshName << '\n';
    auto meshNameHash = hash(meshName.c_str());
    auto pEmberMesh = pResourceManager->getMesh(meshNameHash);
    if (!pEmberMesh) {
      std::vector<PosNormVertex> vertices;
      std::vector<uint32_t> indices;

      for (size_t i = 0; i < pMesh->mNumVertices; i++) {
        auto vertex = pMesh->mVertices[i];
        auto normal = pMesh->mNormals[i];
        vertices.emplace_back(glm::vec3(vertex.x, vertex.y, vertex.z), glm::vec3(normal.x, normal.y, normal.z));
      }

      for (size_t i = 0; i < pMesh->mNumFaces; i++) {
        auto face = pMesh->mFaces[i];
        for (size_t j = 0; j < face.mNumIndices; j++) {
          indices.push_back(face.mIndices[j]);
        }
      }

      Mesh emberMesh(std::span<PosNormVertex>{vertices}, indices);
      pResourceManager->moveMesh(meshNameHash, std::move(emberMesh));
      pEmberMesh = pResourceManager->getMesh(meshNameHash);
    }

    auto pRenderable = root.emplaceChild<Renderable>();
    pRenderable->pVertexArray = pEmberMesh;
    pRenderable->byteOffset = 0;
    pRenderable->vertexCnt = pEmberMesh->getNumVertices();

    auto materialInd = pMesh->mMaterialIndex;
    std::string materialName = "EmberMaterial_";
    materialName += scene->mMaterials[materialInd]->GetName().C_Str();
    auto materialNameHash = hash(materialName.c_str());
    pRenderable->pMaterial = pResourceManager->getMaterial(materialNameHash);

    std::cout << "Loading Mesh: " << meshName << ' ' << materialName << ' ' << materialInd << '\n';
  }

  return root;
}