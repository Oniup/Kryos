/// ------------------------------------------------------------------------ ///
/// This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine) ///
/// @file array_list.c                                                       ///
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

#include "kryos-tools/containers/array_list.h"
#include "kryos-tools/containers/allocator.h"
#include <memory.h>

void destroy_array_list(void* p_list) {
    destroy_dynamic_allocation(p_list);
}

array_list_result_t intl_create_array_list(usize type_size, usize count) {
    allocated_memory_result_t result = create_dynamic_allocation(type_size * count);
    if (result.error_message != NO_ERROR_MESSAGE) {
        ERROR("Failed to create dynamic array: %s", result.error_message);
        return (array_list_result_t) {.failed = true, .p_array = result.p_data};
    }
    return (array_list_result_t) {.failed = false, .p_array = result.p_data};
}

usize intl_get_array_list_size(void* p_list, usize type_size) {
    usize size = get_dynamic_allocation_size(p_list);
    if (size > 0) {
        size = size / type_size;
    }
    return size;
}

usize intl_get_array_list_capacity(void* p_list, usize type_size) {
    usize capacity = get_dynamic_allocation_capacity(p_list);
    if (capacity > 0) {
        capacity = capacity / type_size;
    }
    return capacity;
}
