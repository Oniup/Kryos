/* ------------------------------------------------------------------------ *
 * This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine) *
 * @file memory_allocator.hpp                                               *
 * ------------------------------------------------------------------------ *
 * @copyright (c) 2024 Oniup (https://github.com/Oniup)                     *
 *                                                                          *
 * Licensed under the Apache License, Version 2.0 (the "License");          *
 * you may not use this file except in compliance with the License.         *
 * You may obtain a copy of the License at                                  *
 *                                                                          *
 *   http://www.apache.org/licenses/LICENSE-2.0                             *
 *                                                                          *
 * Unless required by applicable law or agreed to in writing, software      *
 * distributed under the License is distributed on an "AS IS" BASIS,        *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. *
 * See the License for the specific language governing permissions and      *
 * limitations under the License.                                           *
 * ------------------------------------------------------------------------ */

#ifndef KRYOS__TOOLS_CONTAINERS__MEMORY_ALLOCATOR_HPP
#define KRYOS__TOOLS_CONTAINERS__MEMORY_ALLOCATOR_HPP

#include "kryos-tools/defines.hpp"

/**
 * @typedef _kint_allocator_header
 * @brief Dynamic memory allocator structure
 */
typedef struct _kint_allocator_header {
    // @brief Total size in bytes that is initialized and in current use
    usize size;
    // @brief Total allocated buffer size in bytes. Can include uninitialized
    usize capacity;
} _kint_allocator_header_t;

typedef struct allocated_memory_result {
    // @brief NULL if there is no error, otherwise is a compile time string of
    // describing error
    const char* error_message;
    // @brief Pointer to modified data
    void* p_data;
} allocated_memory_result_t;

usize get_dynamic_allocation_size(void* p_data);
usize get_dynamic_allocation_capacity(void* p_data);
// @warning The size cannot exceed the capacity size
bool set_dynamic_allocation_size(void* p_data, usize size);

allocated_memory_result_t create_dynamic_allocation(usize size);

void destroy_dynamic_allocation(void* p_data);

allocated_memory_result_t resize_dynamic_allocation(void* p_data, usize size);
allocated_memory_result_t insert_dynamic_allocation(void* p_data, usize size, usize position);
allocated_memory_result_t resize_dynamic_allocation_capacity(void* p_data, usize capacity);

static _kint_allocator_header_t* _kint_get_dynamic_allocation_data_header(void* p_data);
static void* _kint_get_dynamic_allocation_header_data(_kint_allocator_header_t* p_header);
// @warning Does not check if p_header is NULL, call `resize_dynamic_allocation` to also
// check NULL valid
static allocated_memory_result_t
_kint_resize_dynanmic_allocation_size(_kint_allocator_header_t* p_header, void* p_data, usize size);
// @warning Does not check if p_header is NULL, call `resize_dynamic_allocation_capacity`
// to also check NULL valid
static allocated_memory_result_t
_kint_resize_dynamic_allocation_capacity(_kint_allocator_header_t* p_header, void* p_data,
                                         usize size);

#endif
