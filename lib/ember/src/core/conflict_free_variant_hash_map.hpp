#ifndef CONFLICT_FREE_VARIANT_HASH_MAP
#define CONFLICT_FREE_VARIANT_HASH_MAP

#include <concepts>
#include <memory>
#include <variant>

namespace ember {

template <std::unsigned_integral Key, typename... Types>
class ConflictFreeVariantHashMap {
 public:
  ConflictFreeVariantHashMap(size_t capacity) : m_capacity(capacity), m_memory(std::make_unique<SlotType[]>(capacity)) {}

  template <typename T>
  [[nodiscard]] auto get(Key key) -> T * {
    auto ind = key % m_capacity;
    return std::get_if<T>(&m_memory[ind]);
  }

  template <typename T>
  [[nodiscard]] auto has(Key key) const -> bool {
    auto ind = key % m_capacity;
    return std::holds_alternative<T>(m_memory[ind]);
  }

  template <typename T>
  auto set(Key key, T &&value) -> void {
    auto ind = key % m_capacity;
    m_memory[ind] = std::forward<T>(value);
  }

  auto remove(Key key) -> void {
    auto ind = key % m_capacity;
    m_memory[ind] = Empty();
  }

  auto clear() -> void {
    for(size_t i = 0;i < m_capacity;i++)
      m_memory[i] = Empty();
  }

 private:
  struct Empty {};

  using SlotType = std::variant<Empty, Types...>;

  size_t m_capacity;
  std::unique_ptr<SlotType[]> m_memory;
};

}  // namespace ember

#endif  // CONFLICT_FREE_VARIANT_HASH_MAP