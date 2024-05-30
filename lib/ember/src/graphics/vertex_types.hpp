#ifndef VERTEX_TYPES_HPP
#define VERTEX_TYPES_HPP

#include <concepts>
#include <glm/glm.hpp>

namespace ember {

template <typename T>
concept Vertex = requires() {
  { T::vertexAttrib() } -> std::same_as<void>;
};

struct PosVertex {
  glm::vec3 pos;

  static auto vertexAttrib() -> void;
};

struct PosNormVertex {
  glm::vec3 pos;
  glm::vec3 norm;

  static auto vertexAttrib() -> void;
};

struct PosNormUvVertex {
  glm::vec3 pos;
  glm::vec3 norm;
  glm::vec2 texCoord;

  static auto vertexAttrib() -> void;
};

struct PosColVertex {
  glm::vec3 pos;
  glm::vec3 col;

  static auto vertexAttrib() -> void;
};

}  // namespace ember

#endif  // VERTEX_TYPES_HPP