#ifndef NODE_HPP
#define NODE_HPP

#include <memory>
#include <vector>
namespace ember {

enum class NodeAttribute : unsigned { Object3d = 1, Renderable = (1 << 1), Camera = (1 << 2), Light = (1 << 3) };

class Node {
 public:
  Node();
  virtual ~Node() = default;
  Node(Node &&) = default;
  Node &operator=(Node &&) = default;

  [[nodiscard]] inline auto is(NodeAttribute attribute) const -> bool {
    return m_attributes & static_cast<unsigned>(attribute);
  }

  template <typename T, typename... Args>
  auto emplaceChild(Args &&...args) -> T * {
    m_children.push_back(std::make_unique<T>(std::forward<Args>(args)...));
    return static_cast<T *>(m_children.back().get());
  }

  [[nodiscard]] inline auto getChild(size_t i) const { return m_children[i].get(); }
  auto steal(Node &other) -> void;

  [[nodiscard]] inline auto childCnt() const { return m_children.size(); }

  class Iterator {
   public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = Node *;
    using reference = Node *;

    Iterator(std::vector<std::unique_ptr<Node>>::iterator it);

    [[nodiscard]] inline auto operator*() const -> reference { return m_it->get(); }

    inline auto operator++() -> Iterator & {
      m_it++;
      return *this;
    }
    Iterator operator++(int) {
      Iterator temp = *this;
      ++m_it;
      return temp;
    }

    friend auto operator==(const Iterator &a, const Iterator &b) -> bool;
    friend auto operator!=(const Iterator &a, const Iterator &b) -> bool;

   private:
    std::vector<std::unique_ptr<Node>>::iterator m_it;
  };

  class ConstIterator {
   public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = Node *;
    using reference = const Node *;

    ConstIterator(std::vector<std::unique_ptr<Node>>::const_iterator it);

    [[nodiscard]] inline auto operator*() const -> reference { return m_it->get(); }

    inline auto operator++() -> ConstIterator & {
      m_it++;
      return *this;
    }
    ConstIterator operator++(int) {
      ConstIterator temp = *this;
      ++m_it;
      return temp;
    }

    friend auto operator==(const ConstIterator &a, const ConstIterator &b) -> bool;
    friend auto operator!=(const ConstIterator &a, const ConstIterator &b) -> bool;

   private:
    std::vector<std::unique_ptr<Node>>::const_iterator m_it;
  };

  [[nodiscard]] inline auto begin() -> Iterator { return Iterator(m_children.begin()); }
  [[nodiscard]] inline auto end() -> Iterator { return Iterator(m_children.end()); }

  [[nodiscard]] inline auto begin() const -> ConstIterator { return ConstIterator(m_children.cbegin()); }
  [[nodiscard]] inline auto end() const -> ConstIterator { return ConstIterator(m_children.cend()); }

 protected:
  unsigned m_attributes;
  std::vector<std::unique_ptr<Node>> m_children;
};

auto operator==(const Node::Iterator &a, const Node::Iterator &b) -> bool;
auto operator!=(const Node::Iterator &a, const Node::Iterator &b) -> bool;

auto operator==(const Node::ConstIterator &a, const Node::ConstIterator &b) -> bool;
auto operator!=(const Node::ConstIterator &a, const Node::ConstIterator &b) -> bool;

}  // namespace ember

#endif  // NODE_HPP