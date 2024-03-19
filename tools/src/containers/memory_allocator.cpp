/* ------------------------------------------------------------------------ *
 * This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine) *
 * @file memory_allocator.cpp                                               *
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

#include "kryos-tools/containers/memory_allocator.hpp"
#include <memory.h>
#include <stdlib.h>

usize get_dynamic_allocation_size(void* p_data) {
    if (p_data == nullptr) {
        return 0;
    }
    _kint_allocator_header_t* p_header = _kint_get_dynamic_allocation_data_header(p_data);
    return p_header->size;
}

usize get_dynamic_allocation_capacity(void* p_data) {
    if (p_data == nullptr) {
        return 0;
    }
    _kint_allocator_header_t* p_header = _kint_get_dynamic_allocation_data_header(p_data);
    return p_header->capacity;
}

bool set_dynamic_allocation_size(void* p_data, usize size) {
    _kint_allocator_header_t* p_header = _kint_get_dynamic_allocation_data_header(p_data);
#ifndef NDEBUG
    if (size <= p_header->capacity) {
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
    _kint_allocator_header_t* p_header =
        (_kint_allocator_header_t*)malloc(sizeof(_kint_allocator_header_t) + size);
    if (p_header == nullptr) {
        return (allocated_memory_result_t) {
            .error_message = "Failed to allocate memory, malloc returned nullptr",
            .p_data = nullptr};
    }
    p_header->size = size;
    p_header->capacity = size;
    return (allocated_memory_result_t) {.error_message = NO_ERROR_MESSAGE,
                                        .p_data =
                                            _kint_get_dynamic_allocation_header_data(p_header)};
}

void destroy_dynamic_allocation(void* p_data) {
    if (p_data != nullptr) {
        _kint_allocator_header_t* p_header = _kint_get_dynamic_allocation_data_header(p_data);
        free(p_header);
    }
}

allocated_memory_result_t resize_dynamic_allocation(void* p_data, usize size) {
    _kint_allocator_header_t* p_header = _kint_get_dynamic_allocation_data_header(p_data);
    return _kint_resize_dynanmic_allocation_size(p_header, p_data, size);
}

allocated_memory_result_t insert_dynamic_allocation(void* p_data, usize size, usize pos) {
    _kint_allocator_header_t* p_header = _kint_get_dynamic_allocation_data_header(p_data);
    if (p_header->size < pos) {
        return (allocated_memory_result_t) {
            .error_message = "Cannot insert block into dynamic allocation, position is greater "
                             "than the size",
            .p_data = p_data,
        };
    }
    allocated_memory_result_t resize_result =
        _kint_resize_dynanmic_allocation_size(p_header, p_data, p_header->size + size);
    if (resize_result.error_message != NO_ERROR_MESSAGE) {
        return resize_result;
    }
    bool copyed = memcpy((char*)p_data + (pos + size), (char*)p_data + pos, size) != nullptr;
    if (!copyed) {
        return (allocated_memory_result_t) {
            .error_message =
                "Failed to insert chunk of memory into allocation; \"memcpy\" failed and "
                "returned nullptr ",
            .p_data = _kint_get_dynamic_allocation_header_data(p_header),
        };
    }
    return (allocated_memory_result_t) {
        .error_message = NO_ERROR_MESSAGE,
        .p_data = _kint_get_dynamic_allocation_header_data(p_header),
    };
}

allocated_memory_result_t resize_dynamic_allocation_capacity(void* p_data, usize cap) {
    if (p_data == nullptr) {
        return (allocated_memory_result_t) {
            .error_message = "Cannot resize the capacity of dynamic allocation, p_data its nullptr",
            .p_data = nullptr,
        };
    }
    _kint_allocator_header_t* p_header = _kint_get_dynamic_allocation_data_header(p_data);
    return _kint_resize_dynamic_allocation_capacity(p_header, p_data, cap);
}

_kint_allocator_header_t* _kint_get_dynamic_allocation_data_header(void* p_data) {
    _kint_allocator_header_t* p_header = (_kint_allocator_header_t*)p_data;
    p_header = p_header - 1;
    return p_header;
}

void* _kint_get_dynamic_allocation_header_data(_kint_allocator_header_t* p_header) {
    p_header = p_header + 1;
    return (void*)p_header;
}

allocated_memory_result_t _kint_resize_dynanmic_allocation_size(_kint_allocator_header_t* p_header,
                                                                void* p_data, usize size) {
    if (size > p_header->size) {
        allocated_memory_result_t result =
            _kint_resize_dynamic_allocation_capacity(p_header, p_data, size);
        if (result.error_message != NO_ERROR_MESSAGE) {
            return result;
        }
        p_header = _kint_get_dynamic_allocation_data_header(result.p_data);
    }
    p_header->size = size;
    return (allocated_memory_result_t) {.error_message = NO_ERROR_MESSAGE,
                                        .p_data =
                                            _kint_get_dynamic_allocation_header_data(p_header)};
}

allocated_memory_result_t
_kint_resize_dynamic_allocation_capacity(_kint_allocator_header_t* p_header, void* p_data,
                                         usize size) {
    _kint_allocator_header_t* p_tmp =
        (_kint_allocator_header_t*)realloc(p_header, sizeof(_kint_allocator_header_t) + size);
    if (p_tmp == nullptr) {
        return (allocated_memory_result_t) {
            .error_message =
                "Failed to resize memory allocation capacity; realloc failed and returned nullptr",
            .p_data = p_data};
    }
    p_header = p_tmp;
    p_header->capacity = size;
    p_data = _kint_get_dynamic_allocation_header_data(p_header);
    return (allocated_memory_result_t) {.error_message = NO_ERROR_MESSAGE, .p_data = p_data};
}
