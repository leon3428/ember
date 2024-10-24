#ifndef RESOURCE_INDEX_HPP
#define RESOURCE_INDEX_HPP

#include "../core/variant_hash_map.hpp"
#include "../core/utils.hpp"
#include "resource_descriptions.hpp"

namespace ember {

class ResourceIndex {
 public:
  template <typename T>
  [[nodiscard]] inline auto getDescription(Identifier idn) const -> const T * {
    return m_resourceIndex.get<T>(idn);
  }

  template <typename T>
  inline auto setDescription(Identifier idn, T &&description) -> void {
    m_resourceIndex.set(idn, std::forward<T>(description));
  }

 private:
  VariantHashMap<Identifier, IdentifierHash, resource_desc::Object, resource_desc::Texture, resource_desc::Curve> m_resourceIndex;
};

inline auto getResourceIndex() -> ResourceIndex * {
  static ResourceIndex resourceIndex;
  return &resourceIndex;
}

}  // namespace ember

#endif  // RESOURCE_INDEX_HPP