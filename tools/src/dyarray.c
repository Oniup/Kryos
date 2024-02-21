/// ------------------------------------------------------------------------ ///
/// This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine) ///
/// @file dyarray.c                                                          ///
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

#include "kryos-tools/dyarray.h"
#include "kryos-tools/allocator.h"
#include <memory.h>

void destroy_dyarray(void* p_dyarray) {
    destroy_dynamic_allocation(p_dyarray);
}

dyarray_result_t intl_create_dyarray(usize type_size, usize count) {
    allocated_memory_result_t result = create_dynamic_allocation(type_size * count);
    if (result.error_message != NO_ERROR_MESSAGE) {
        ERROR("Failed to create dynamic array: %s", result.error_message);
        return (dyarray_result_t) {.failed = true, .p_dyarray = result.p_data};
    }
    return (dyarray_result_t) {.failed = false, .p_dyarray = result.p_data};
}

usize intl_get_dyarray_size(void* p_dyarray, usize type_size) {
    usize size = get_dynamic_allocation_size(p_dyarray);
    if (size > 0) {
        size = size / type_size;
    }
    return size;
}

usize intl_get_dyarray_capacity(void* p_dyarray, usize type_size) {
    usize capacity = get_dynamic_allocation_capacity(p_dyarray);
    if (capacity > 0) {
        capacity = capacity / type_size;
    }
    return capacity;
}

dyarray_result_t intl_resize_dyarray(void* p_dyarray, usize type_size, usize count) {
    if (p_dyarray != NULL) {
        usize size = get_dynamic_allocation_size(p_dyarray);
        usize insert_size = type_size * count;
        allocated_memory_result_t result = resize_dynamic_allocation(p_dyarray, size + insert_size);
        if (result.error_message != NO_ERROR_MESSAGE) {
            ERROR("Failed to push back data into dynamic list: %s", result.error_message);
            return (dyarray_result_t) {.failed = true, .p_dyarray = p_dyarray};
        }
        return (dyarray_result_t) {
            .failed = false,
            .p_dyarray = result.p_data,
        };
    }
    ERROR("Failed to resize dynamic array: Given array is NULL");
    return (dyarray_result_t) {
        .failed = true,
        .p_dyarray = NULL,
    };
}

dyarray_result_t intl_resize_dyarray_capacity(void* p_dyarray, usize type_size,
                                              usize capacity_count) {
    return (dyarray_result_t) {.failed = true, .p_dyarray = p_dyarray};
}

dyarray_result_t intl_push_dyarray_data(void* p_dyarray, usize type_size,
                                        DYARRAY_insert_type_t insert_type, usize count,
                                        usize position, void* p_data) {
    if (p_data != NULL) {
        dyarray_result_t result = intl_resize_dyarray(p_dyarray, type_size, count);
        if (result.failed) {
            ERROR("Failed to push dyarray data due to resize fail");
            return result;
        }
        p_dyarray = result.p_dyarray;
        switch (insert_type) {
            case DYARRAY_INSERT_TYPE_BACK:
                return intl_push_dyarray_data_back(p_dyarray, type_size * count, p_data);
            case DYARRAY_INSERT_TYPE_FRONT:
                return intl_push_dyarray_data_front(p_dyarray, type_size * count, p_data);
            case DYARRAY_INSERT_TYPE_ANY:
                return intl_insert_dyarray_data(p_dyarray, type_size * position, type_size * count,
                                                p_data);
        };
    }
    return (dyarray_result_t) {.failed = false, .p_dyarray = p_dyarray};
}

dyarray_result_t intl_push_dyarray_data_back(void* p_dyarray, usize size, void* p_data) {
    usize old_size = get_dynamic_allocation_size(p_dyarray) - size;
    errno_t error = memcpy_s(p_dyarray + old_size, size, p_data, size);
    if (error != 0) {
        ERROR("Failed to push back data into dynamic array: memcpy_s failed to copy p_data and "
              "returned error code %d",
              error);
        return (dyarray_result_t) {.failed = true, .p_dyarray = p_dyarray};
    }
    return (dyarray_result_t) {.failed = false, .p_dyarray = p_dyarray};
}

dyarray_result_t intl_push_dyarray_data_front(void* p_dyarray, usize size, void* p_data) {
    usize old_size = get_dynamic_allocation_size(p_dyarray) - size;
    errno_t error = memcpy_s(p_dyarray + size, old_size, p_dyarray, old_size);
    if (error != 0) {
        ERROR("Failed to shift original data over to the left to make room for the new data at "
              "front of dynamic array: memecpy_s failed and returned error code %d",
              error);
        return (dyarray_result_t) {.failed = true, .p_dyarray = p_dyarray};
    }
    error = memcpy_s(p_dyarray, size, p_data, size);
    if (error != 0) {
        ERROR("Failed to push back data into dynamic array: memcpy_s failed to copy p_data and "
              "returned error code %d",
              error);
        return (dyarray_result_t) {.failed = true, .p_dyarray = p_dyarray};
    }
    return (dyarray_result_t) {.failed = true, .p_dyarray = p_dyarray};
}

dyarray_result_t intl_insert_dyarray_data(void* p_dyarray, usize pos, usize size, void* p_data) {
    if (p_dyarray != NULL && p_data != NULL) {
    }
    return (dyarray_result_t) {.failed = false, .p_dyarray = p_dyarray};
}
