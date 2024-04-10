#ifndef MY_GLM_HPP
#define MY_GLM_HPP

#include <glm/glm.hpp>

namespace my_glm {

auto translate3D(glm::vec3 translateVector) -> glm::mat4;
auto scale3D(glm::vec3 scaleVector) -> glm::mat4;
auto rotate3D(glm::vec3 axis, float angle) -> glm::mat4;
auto lookAtMatrix(glm::vec3 eye, glm::vec3 center, glm::vec3 viewUp) -> glm::mat4;
auto frustum(float l, float r, float b, float t, float n, float f) -> glm::mat4;

}  // namespace my_glm

#endif  // MY_GLM_HPP