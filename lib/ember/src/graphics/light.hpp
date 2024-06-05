#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "object3d.hpp"

namespace ember {

class Light : public Object3d {
 public:
  Light();
  
  glm::vec4 diffuseIntensity;
  glm::vec4 specularIntensity;
  float angle;
};

}  // namespace ember

#endif  // LIGHT_HPP