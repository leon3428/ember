#include "project_loader.hpp"
#include "utils.hpp"

#include <rapidjson/document.h>
#include <rapidjson/error/en.h>
#include <iostream>
#include "../resource_manager/resource_index.hpp"

auto ember::project::load(std::filesystem::path path) -> void {
  auto contents = readFile(path / "project.json");

  if (!contents) {
    std::cerr << "Project folder not found\n";
    return;
  }

  rapidjson::Document document;
  document.Parse(contents->c_str());

  if (document.HasParseError()) {
    std::cerr << "JSON parse error: " << rapidjson::GetParseError_En(document.GetParseError()) << " (offset "
              << document.GetErrorOffset() << ")\n";
    return;
  }

  auto resourceIndex = getResourceIndex();

  if (document["resources"].IsArray()) {
    auto resources = document["resources"].GetArray();

    for (auto &resource : resources) {
      if (!resource["name"].IsString() || !resource["type"].IsString()) continue;

      auto nameHash = hash(resource["name"].GetString());
      auto type = resource["type"].GetString();

      if (strcmp(type, "object") == 0) {
        auto objectDesc = resource_desc::load<resource_desc::Object>(resource);
        objectDesc.path = path / objectDesc.path;
        resourceIndex->setDescription(nameHash, objectDesc);
      }
    }
  }
}