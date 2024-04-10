#include "my_glm.hpp"
#include <cmath>

auto sq(float x) -> float { return x * x; }

auto my_glm::translate3D(glm::vec3 translateVector) -> glm::mat4 {
  glm::mat4 ret(1.0f);

  ret[3][0] = translateVector[0];
  ret[3][1] = translateVector[1];
  ret[3][2] = translateVector[2];

  return ret;
}

auto my_glm::scale3D(glm::vec3 scaleVector) -> glm::mat4 {
  glm::mat4 ret(1.0f);

  ret[0][0] = scaleVector[0];
  ret[1][1] = scaleVector[1];
  ret[2][2] = scaleVector[2];

  return ret;
}

auto my_glm::rotate3D(glm::vec3 axis, float angle) -> glm::mat4 {
  glm::mat4 ret(1.0f);

  ret[0][0] = std::cos(angle) + sq(axis.x) * (1.0f - std::cos(angle));
  ret[0][1] = axis.x * axis.y * (1.0f - std::cos(angle)) + axis.z * std::sin(angle);
  ret[0][2] = axis.x * axis.z * (1.0f - std::cos(angle)) - axis.y * std::sin(angle);

  ret[1][0] = axis.x * axis.y * (1.0f - std::cos(angle)) - axis.z * std::sin(angle);
  ret[1][1] = std::cos(angle) + sq(axis.y) * (1.0f - std::cos(angle));
  ret[1][2] = axis.y * axis.z * (1.0f - std::cos(angle)) + axis.x * std::sin(angle);

  ret[2][0] = axis.x * axis.z * (1.0f - std::cos(angle)) + axis.y * std::sin(angle);
  ret[2][1] = axis.y * axis.z * (1.0f - std::cos(angle)) - axis.x * std::sin(angle);
  ret[2][2] = std::cos(angle) + sq(axis.z) * (1.0f - std::cos(angle));

  return ret;
}

auto my_glm::lookAtMatrix(glm::vec3 eye, glm::vec3 center, glm::vec3 viewUp) -> glm::mat4 {
  glm::vec3 forward = glm::normalize(center - eye);
  glm::vec3 right = glm::normalize(glm::cross(forward, viewUp));
  glm::vec3 newUp = glm::cross(right, forward);

  glm::mat4 rotationMatrix(1.0f);
  rotationMatrix[0][0] = right.x;
  rotationMatrix[1][0] = right.y;
  rotationMatrix[2][0] = right.z;

  rotationMatrix[0][1] = newUp.x;
  rotationMatrix[1][1] = newUp.y;
  rotationMatrix[2][1] = newUp.z;

  rotationMatrix[0][2] = -forward.x;
  rotationMatrix[1][2] = -forward.y;
  rotationMatrix[2][2] = -forward.z;

  glm::mat4 translationMatrix(1.0f);
  translationMatrix[3][0] = -eye.x;
  translationMatrix[3][1] = -eye.y;
  translationMatrix[3][2] = -eye.z;

  return rotationMatrix * translationMatrix;
}

auto my_glm::frustum(float l, float r, float b, float t, float n, float f) -> glm::mat4 {
  glm::mat4 ret(0.0f);

  ret[0][0] = 2.0f * n / (r - l);
  ret[1][1] = 2.0f * n / (t - b);
  ret[2][0] = (r + l) / (r - l);
  ret[2][1] = (t + b) / (t - b);
  ret[2][2] = -(f + n) / (f - n);
  ret[2][3] = -1;
  ret[3][2] = -2 * f * n / (f - n);

  return ret;
}
