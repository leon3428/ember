#include "camera.hpp"
#include "../core/utils.hpp"
#include "glm/geometric.hpp"
#include "glm/gtc/quaternion.hpp"
#include "node.hpp"

ember::Camera::Camera() { m_attributes |= static_cast<unsigned>(NodeAttribute::Camera); }

