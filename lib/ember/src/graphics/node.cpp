#include "node.hpp"

ember::Node::Node() : m_attributes(0) {}

auto ember::Node::steal(Node &other) -> void {
  for (auto &child : other.m_children) {
    m_children.push_back(std::move(child));
  }

  other.m_children.clear();
}

ember::Node::Iterator::Iterator(std::vector<std::unique_ptr<Node>>::iterator it) : m_it(it) {}

auto ember::operator==(const ember::Node::Iterator &a, const ember::Node::Iterator &b) -> bool {
  return a.m_it == b.m_it;
}
auto ember::operator!=(const ember::Node::Iterator &a, const ember::Node::Iterator &b) -> bool {
  return a.m_it != b.m_it;
}

ember::Node::ConstIterator::ConstIterator(std::vector<std::unique_ptr<Node>>::const_iterator it) : m_it(it) {}

auto ember::operator==(const ember::Node::ConstIterator &a, const ember::Node::ConstIterator &b) -> bool {
  return a.m_it == b.m_it;
}
auto ember::operator!=(const ember::Node::ConstIterator &a, const ember::Node::ConstIterator &b) -> bool {
  return a.m_it != b.m_it;
}
