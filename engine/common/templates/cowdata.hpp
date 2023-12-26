#ifndef KRYOS__COMMON_TEMPLATES__COWDATA_HPP_
#define KRYOS__COMMON_TEMPLATES__COWDATA_HPP_

#include "common/defines.hpp"
#include "core/memory.hpp"

namespace kryos {

template <typename T>
class CowData {
public:
  CowData() = default;

  inline ui32_t* get_ref_count()
  {
    if (_ptr != nullptr) {
      MemoryHeader* header = (MemoryHeader*)_ptr - 1;
      return &header->ref_count;
    }
    return nullptr;
  }

  inline ui32_t* get_block_size()
  {
    if (_ptr != nullptr) {
      MemoryHeader* header = (MemoryHeader*)_ptr - 1;
      return &header->block_size;
    }
    return nullptr;
  }

  void copy_on_write()
  {
    if (_ptr != nullptr) {
    }
  }

private:
  T* _ptr = nullptr;
};

} // namespace kryos

#endif
