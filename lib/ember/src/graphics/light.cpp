#include "light.hpp"
#include "node.hpp"

ember::Light::Light() {
  m_attributes |= static_cast<unsigned>(NodeAttribute::Light);
}