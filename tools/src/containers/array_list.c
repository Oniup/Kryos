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
#include <math.h>
#include <memory.h>

void destroy_array_list(void* p_list) {
    destroy_dynamic_allocation(p_list);
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

array_list_result_t intl_create_array_list_uninitialized(usize type_size, usize capacity_count) {
    allocated_memory_result_t result = create_dynamic_allocation(type_size * capacity_count);
    if (result.error_message != NO_ERROR_MESSAGE) {
        ERROR(
            "Failed to create uninitialized array list of size %zu, type_size: %zu, count: %zu: %s",
            type_size * capacity_count, type_size, capacity_count, result.error_message);
        return (array_list_result_t) {.failed = true, .p_data = NULL};
    }
    void* p_data = result.p_data;
    set_dynamic_allocation_size(p_data, 0);
    return (array_list_result_t) {.failed = false, .p_data = p_data};
}

array_list_result_t intl_resize_array_list_size(void* p_list, usize type_size, usize count) {
    usize capacity = get_dynamic_allocation_capacity(p_list);
    usize new_size = get_dynamic_allocation_size(p_list) + type_size * count;
    if (new_size > capacity) {
        array_list_result_t result = intl_resize_array_list_capacity(p_list, type_size, count);
        if (result.failed) {
            return result;
        }
        p_list = result.p_data;
    }
    b8 result = set_dynamic_allocation_size(p_list, new_size);
    if (!result) {
        ERROR("Failed to resize array list to %zu, type_size: %zu, count: %zu", type_size * count,
              type_size, count);
        return (array_list_result_t) {.failed = true, .p_data = p_list};
    }
    return (array_list_result_t) {.failed = false, .p_data = p_list};
}

array_list_result_t intl_resize_array_list_capacity(void* p_list, usize type_size, usize count) {
    usize capacity_increase =
        (usize)ceil((f64)(type_size * count) / (f64)ARRAY_LIST_DEFAULT_CAPACITY_INCREASE_COUNT);
    allocated_memory_result_t result = resize_dynamic_allocation_capacity(
        p_list, get_dynamic_allocation_capacity(p_list) +
                    capacity_increase * (type_size * ARRAY_LIST_DEFAULT_CAPACITY_INCREASE_COUNT));
    if (result.error_message != NO_ERROR_MESSAGE) {
        ERROR("Failed to resize array list capacity to %zu, type_size: %zu, count: %zu",
              type_size * count, type_size, count);
        return (array_list_result_t) {.failed = true, .p_data = p_list};
    }
    p_list = result.p_data;
    return (array_list_result_t) {.failed = false, .p_data = p_list};
}

array_list_result_t intl_push_array_list_data_back(void* p_list, usize type_size, usize count,
                                                   void* p_data) {
    usize old_size = intl_get_array_list_size(p_list, type_size);
    array_list_result_t result = intl_resize_array_list_size(p_list, type_size, count);
    if (result.failed) {
        return result;
    }
    p_list = result.p_data;
    usize size = intl_get_array_list_size(p_list, type_size);
    if (size == 0) {
        return (array_list_result_t) {.failed = true, .p_data = p_list};
    }
    usize p_data_size = type_size * count;
    errno_t error = memcpy_s(p_list + type_size * old_size, p_data_size, p_data, p_data_size);
    if (error != 0) {
        ERROR("Failed to memcpy_s as the error code resulted in %d", error);
        return (array_list_result_t) {.failed = true, .p_data = p_list};
    }
    return (array_list_result_t) {.failed = false, .p_data = p_list};
}

array_list_result_t intl_push_array_list_data_front(void* p_list, usize type_size, usize count,
                                                    void* p_data) {
    usize old_size = intl_get_array_list_size(p_list, type_size);
    array_list_result_t result = intl_resize_array_list_size(p_list, type_size, count);
    if (result.failed) {
        return result;
    }
    p_list = result.p_data;
    usize size = intl_get_array_list_size(p_list, type_size);
    if (size == 0) {
        return (array_list_result_t) {.failed = true, .p_data = p_list};
    }
    usize p_data_size = type_size * count;
    // Shift old data over
    errno_t error =
        memcpy_s(p_list + p_data_size, old_size * type_size, p_list, old_size * type_size);
    if (error != 0) {
        ERROR("Failed to shift original array list data over to make room for the new data at "
              "front: memcpy_s failed and returned error code %d",
              error);
        return (array_list_result_t) {.failed = true, .p_data = p_list};
    }
    // Copy New Data
    error = memcpy_s(p_list, p_data_size, p_data, p_data_size);
    if (error != 0) {
        ERROR("Failed to memcpy_s as the error code resulted in %d", error);
        return (array_list_result_t) {.failed = true, .p_data = p_list};
    }
    return (array_list_result_t) {.failed = false, .p_data = p_list};
}
