#ifndef VARIANT_HASH_MAP
#define VARIANT_HASH_MAP

#include <unordered_map>
#include <variant>

namespace ember {

template <typename Key, typename Hash, typename... Types>
class VariantHashMap {
 public:

  template <typename T>
  [[nodiscard]] auto get(Key key) -> T * {
    if(!m_map.contains(key))
      return nullptr;

    return std::get_if<T>(&m_map.at(key));
  }

  template <typename T>
  [[nodiscard]] auto get(Key key) const -> const T * {
    if(!m_map.contains(key))
      return nullptr;

    return std::get_if<T>(&m_map.at(key));
  }

  template <typename T>
  [[nodiscard]] auto contains(Key key) const -> bool {
    if(!m_map.contains(key))
      return false;

    return std::holds_alternative<T>(m_map.at(key));
  }

  template <typename T>
  auto set(Key key, T &&value) -> void {
    m_map[key] = std::forward<T>(value);
  }

  auto remove(Key key) -> void {
    m_map.erase(key);
  }

  auto clear() -> void {
    m_map.clear();
  }

 private:
  struct Empty {};

  std::unordered_map<Key, std::variant<Empty, Types...>, Hash> m_map;
};

}  // namespace ember

#endif  // VARIANT_HASH_MAP