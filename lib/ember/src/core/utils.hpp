#ifndef CORE_UTILS_HPP
#define CORE_UTILS_HPP

#include <filesystem>
#include <optional>
#include <string>

namespace ember {
std::optional<std::string> readFile(std::filesystem::path path);

struct Identifier {
  uint32_t id = 0;

  bool operator==(const Identifier other) const { return this->id == other.id; }

  using entity_type = uint32_t;

  constexpr operator uint32_t() const { return id; }
};

struct IdentifierHash {
  size_t operator()(const Identifier id) const { return id.id; }
};

constexpr Identifier hash(const char *str) {
  uint32_t hash = 5381;
  char c;

  while ((c = *str++)) hash = ((hash << 5) + hash) + c;

  return {hash};
}
}  // namespace ember

inline constexpr ember::Identifier operator""_id(const char *str, size_t) { return ember::hash(str); }

#endif  // CORE_UTILS_HPP