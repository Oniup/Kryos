/// ------------------------------------------------------------------------------------------------
/// This file is part of os Engine (https://github.com/Oniup/osEngine)
/// @file allocator.c
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

#include "kryos-tools/allocator.h"

#include <memory.h>
#include <stdlib.h>

/// @brief Dynamic memory allocator structure.
typedef struct intl_header {
    usize size;
    usize cap;
} intl_header_t;

intl_header_t* intl_get_data_header(void* p_data);
void* intl_get_header_data(intl_header_t* p_header);
/// @warning Does not check if p_header is NULL, call `resize_dynamic_allocation` to also check NULL
/// valid
allocated_memory_result_t intl_resize_size(intl_header_t* p_header, void* p_data, usize size);
/// @warning Does not check if p_header is NULL, call `resize_dynamic_allocation_capacity` to also
/// check NULL valid
allocated_memory_result_t intl_resize_capacity(intl_header_t* p_header, void* p_data, usize size);

usize get_dynamic_allocation_size(void* p_data) {
    if (p_data == NULL) {
        return 0;
    }
    intl_header_t* p_header = intl_get_data_header(p_data);
    return p_header->size;
}

usize get_dynamic_allocation_capacity(void* p_data) {
    if (p_data == NULL) {
        return 0;
    }
    intl_header_t* p_header = intl_get_data_header(p_data);
    return p_header->cap;
}

b8 set_dynamic_allocation_size(void* p_data, usize size) {
    if (p_data == NULL) {
        return false;
    }
    intl_header_t* p_header = intl_get_data_header(p_data);
#ifndef NDEBUG
    if (size <= p_header->cap) {
        p_header->size = size;
    } else {
        return false;
    }
#else
    p_header->size = size;
#endif
    return true;
}

allocated_memory_result_t create_dynamic_allocation(usize size) {
    if (size <= 0) {
        return (allocated_memory_result_t) {.err_msg = "Size given is 0, cannot allocate memory",
                                            .p_data = NULL};
    }
    intl_header_t* p_header = malloc(sizeof(intl_header_t) + size);
    if (p_header == NULL) {
        return (allocated_memory_result_t) {
            .err_msg = "Failed to allocate memory, malloc returned NULL", .p_data = NULL};
    }
    p_header->size = size;
    p_header->cap = size;
    return (allocated_memory_result_t) {.err_msg = NO_ALLOCATED_MEMORY_ERROR,
                                        .p_data = intl_get_header_data(p_header)};
}

void destroy_dynamic_allocation(void* p_data) {
    if (p_data != NULL) {
        intl_header_t* p_header = intl_get_data_header(p_data);
        free(p_header);
    }
}

allocated_memory_result_t resize_dynamic_allocation(void* p_data, usize size) {
    if (p_data == NULL) {
        return (allocated_memory_result_t) {
            .err_msg = "Cannot resize the size of dynamic allocation, p_data its NULL",
            .p_data = NULL,
        };
    }
    intl_header_t* p_header = intl_get_data_header(p_data);
    return intl_resize_size(p_header, p_data, size);
}

allocated_memory_result_t insert_dynamic_allocation(void* p_data, usize size, usize pos) {
    intl_header_t* p_header = intl_get_data_header(p_data);
    if (p_header->size < pos) {
        return (allocated_memory_result_t) {
            .err_msg =
                "Cannot insert block into dynamic allocation, position is greater than the size",
            .p_data = p_data,
        };
    }
    allocated_memory_result_t resize_res =
        intl_resize_size(p_header, p_data, p_header->size + size);
    if (resize_res.err_msg != NO_ALLOCATED_MEMORY_ERROR) {
        return resize_res;
    }
    b8 copyed = memcpy((char*)p_data + (pos + size), (char*)p_data + pos, size) != NULL;
    if (!copyed) {
        return (allocated_memory_result_t) {
            .err_msg = "Failed to insert chunk of memory into allocation; \"memcpy\" failed and "
                       "returned NULL ",
            .p_data = intl_get_header_data(p_header),
        };
    }
    return (allocated_memory_result_t) {
        .err_msg = NO_ALLOCATED_MEMORY_ERROR,
        intl_get_header_data(p_header),
    };
}

allocated_memory_result_t resize_dynamic_allocation_capacity(void* p_data, usize cap) {
    if (p_data == NULL) {
        return (allocated_memory_result_t) {
            .err_msg = "Cannot resize the capacity of dynamic allocation, p_data its NULL",
            .p_data = NULL,
        };
    }
    intl_header_t* p_header = intl_get_data_header(p_data);
    return intl_resize_capacity(p_header, p_data, cap);
}

intl_header_t* intl_get_data_header(void* p_data) {
    intl_header_t* p_header = (intl_header_t*)p_data;
    p_header = p_header - 1;
    return p_header;
}

void* intl_get_header_data(intl_header_t* p_header) {
    p_header = p_header + 1;
    return (void*)p_header;
}

allocated_memory_result_t intl_resize_size(intl_header_t* p_header, void* p_data, usize size) {
    if (size > p_header->size) {
        allocated_memory_result_t res = intl_resize_capacity(p_header, p_data, size);
        if (res.err_msg != NO_ALLOCATED_MEMORY_ERROR) {
            return res;
        }
        p_header = intl_get_data_header(res.p_data);
    }
    p_header->size = size;
    return (allocated_memory_result_t) {.err_msg = NO_ALLOCATED_MEMORY_ERROR,
                                        .p_data = intl_get_header_data(p_header)};
}

allocated_memory_result_t intl_resize_capacity(intl_header_t* p_header, void* p_data, usize size) {
    intl_header_t* p_tmp = realloc(p_header, sizeof(intl_header_t) + size);
    if (p_tmp == NULL) {
        return (allocated_memory_result_t) {
            .err_msg =
                "Failed to resize memory allocation capacity; realloc failed and returned NULL",
            .p_data = p_data};
    }
    p_header = p_tmp;
    p_header->cap = size;
    p_data = intl_get_header_data(p_header);
    return (allocated_memory_result_t) {.err_msg = NO_ALLOCATED_MEMORY_ERROR, .p_data = p_data};
}
