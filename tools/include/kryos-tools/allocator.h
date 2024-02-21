/// ------------------------------------------------------------------------ ///
/// This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine) ///
/// @file allocator.h                                                        ///
/// ------------------------------------------------------------------------ ///
/// @copyright (c) 2024 Oniup (https://github.com/Oniup)                     ///
///                                                                          ///
/// Licensed under the Apache License, Version 2.0 (the "License");          ///
/// you may not use this file except in compliance with the License.         ///
/// You may obtain a copy of the License at                                  ///
///                                                                          ///
///   http://www.apache.org/licenses/LICENSE-2.0                             ///
///                                                                          ///
/// Unless required by applicable law or agreed to in writing, software      ///
/// distributed under the License is distributed on an "AS IS" BASIS,        ///
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. ///
/// See the License for the specific language governing permissions and      ///
/// limitations under the License.                                           ///
/// ------------------------------------------------------------------------ ///

#ifndef KRYOS__TOOLS__ALLOCATOR_H
#define KRYOS__TOOLS__ALLOCATOR_H
#ifdef __cplusplus
extern "C" {
#endif

#include "kryos-tools/defines.h"

/// @brief Dynamic memory allocator structure.
typedef struct intl_allocator_header {
    /// @brief Total size in bytes that is initialized and in current use
    usize size;
    /// @brief Total allocated buffer size in bytes. Can include uninitialized
    usize capacity;
} intl_allocator_header_t;

typedef struct allocated_memory_result {
    /// @brief NULL if there is no error, otherwise is a compile time string of
    /// describing error
    const char* error_message;
    /// @brief Pointer to modified data
    void* p_data;
} allocated_memory_result_t;

KRYAPI usize get_dynamic_allocation_size(void* p_data);
KRYAPI usize get_dynamic_allocation_capacity(void* p_data);
/// @warning The size cannot exceed the capacity size
KRYAPI b8 set_dynamic_allocation_size(void* p_data, usize size);

KRYAPI allocated_memory_result_t create_dynamic_allocation(usize size);

KRYAPI void destroy_dynamic_allocation(void* p_data);

KRYAPI allocated_memory_result_t resize_dynamic_allocation(void* p_data, usize size);
KRYAPI allocated_memory_result_t insert_dynamic_allocation(void* p_data, usize size,
                                                           usize position);
KRYAPI allocated_memory_result_t resize_dynamic_allocation_capacity(void* p_data, usize capacity);

#ifdef __cplusplus
}
#endif
#endif
