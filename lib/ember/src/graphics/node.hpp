#ifndef NODE_HPP
#define NODE_HPP

#include <memory>
#include <vector>
namespace ember {

enum class NodeAttribute : unsigned { 
  Object3d = 1, 
  Renderable = (1 << 1),
  Camera = (1 << 2)
};

class Node {
 public:
  Node();
  virtual ~Node() = default;

  [[nodiscard]] inline auto is(NodeAttribute attribute) const -> bool {
    return m_attributes & static_cast<unsigned>(attribute);
  }

  std::vector<std::unique_ptr<Node>> children;

 protected:
  unsigned m_attributes;
};

}  // namespace ember

#endif  // NODE_HPP