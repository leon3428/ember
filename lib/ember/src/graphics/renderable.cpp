#include "renderable.hpp"

ember::Renderable::Renderable() { m_attributes |= static_cast<unsigned>(NodeAttribute::Renderable); }