/// ------------------------------------------------------------------------------------------------
/// This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine)
/// @file allocator.h
/// ------------------------------------------------------------------------------------------------
/// @copyright
/// Copyright (c) 2024 Oniup (https://github.com/Oniup/)
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///   http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
/// ------------------------------------------------------------------------------------------------

#ifndef KRYOS__TOOLS__ALLOCATOR_H
#define KRYOS__TOOLS__ALLOCATOR_H
#include <vcruntime_string.h>
#ifdef __cplusplus
extern "C" {
#endif

#include "kryos-tools/defines.h"

#define NO_ALLOCATED_MEMORY_ERROR NULL

typedef struct allocated_memory_result {
    /// @brief NULL if there is no error, otherwise is a compile time string of
    /// describing error
    const char* err_msg;
    /// @brief Pointer to modified data
    void* p_data;
} allocated_memory_result_t;

KRYAPI usize get_dynamic_allocation_size(void* p_data);
KRYAPI usize get_dynamic_allocation_capacity(void* p_data);

KRYAPI allocated_memory_result_t create_dynamic_allocation(usize size);

KRYAPI void destroy_dynamic_allocation(void* p_data);

KRYAPI allocated_memory_result_t resize_dynamic_allocation(void* p_data, usize size);
KRYAPI allocated_memory_result_t insert_dynamic_allocation(void* p_data, usize size, usize pos);
KRYAPI allocated_memory_result_t resize_dynamic_allocation_capacity(void* p_data, usize cap);

#ifdef __cplusplus
}
#endif
#endif
