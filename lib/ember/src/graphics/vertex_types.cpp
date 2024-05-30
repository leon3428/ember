#include "vertex_types.hpp"

#include <glad/glad.h>

#include <iostream>

auto ember::PosVertex::vertexAttrib() -> void {
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(PosVertex),
                        reinterpret_cast<void *>(offsetof(PosVertex, pos)));
  glEnableVertexAttribArray(0);
}

auto ember::PosNormVertex::vertexAttrib() -> void {
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(PosNormVertex),
                        reinterpret_cast<void *>(offsetof(PosNormVertex, pos)));
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(PosNormVertex),
                        reinterpret_cast<void *>(offsetof(PosNormVertex, norm)));
  glEnableVertexAttribArray(1);
}

auto ember::PosNormUvVertex::vertexAttrib() -> void {
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(PosNormUvVertex),
                        reinterpret_cast<void *>(offsetof(PosNormUvVertex, pos)));
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(PosNormUvVertex),
                        reinterpret_cast<void *>(offsetof(PosNormUvVertex, norm)));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(PosNormUvVertex),
                        reinterpret_cast<void *>(offsetof(PosNormUvVertex, texCoord)));
  glEnableVertexAttribArray(2);
}

auto ember::PosColVertex::vertexAttrib() -> void {
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(PosColVertex),
                        reinterpret_cast<void *>(offsetof(PosColVertex, pos)));
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(PosColVertex),
                        reinterpret_cast<void *>(offsetof(PosColVertex, col)));
  glEnableVertexAttribArray(1);
}