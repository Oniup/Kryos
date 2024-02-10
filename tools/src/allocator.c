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

allocator_t init_allocator(usize size) {
    allocator_t alloc = {.size = size, .p_data = NULL};
    if (size > 0) {
        allocate_memory(&alloc, size);
    }
    return alloc;
}

void deinit_allocator(allocator_t* p_alloc) {
    if (p_alloc->p_data != NULL && p_alloc->size > 0) {
        free(p_alloc->p_data);
        p_alloc->p_data = NULL;
        p_alloc->size = 0;
    }
}

allocator_result_t allocate_memory(allocator_t* p_alloc, usize size) {
#ifndef NDEBUG
    if (p_alloc->p_data != NULL) {
        return (allocator_result_t) {
            .err_msg = "Cannot allocate memory when allocation already exists",
            .p_ptr = p_alloc->p_data,
        };
    }
#endif
    p_alloc->p_data = malloc(size);
    if (p_alloc->p_data != NULL) {
        p_alloc->size = size;
        return (allocator_result_t) {
            .err_msg = ALLOCATOR_RESULT_PASSED,
            .p_ptr = p_alloc->p_data,
        };
    }
    return (allocator_result_t) {
        .err_msg = "Failed to allocate memory; \"malloc\" failed and returned NULL",
        .p_ptr = p_alloc->p_data,
    };
}

allocator_result_t resize_memory(allocator_t* p_alloc, usize size) {
    if (p_alloc->p_data != NULL) {
        void* tmp = realloc(p_alloc->p_data, size);
        if (tmp != NULL) {
            usize offset = p_alloc->size;
            p_alloc->p_data = tmp;
            p_alloc->size = size;
            return (allocator_result_t) {
                .err_msg = ALLOCATOR_RESULT_PASSED,
                .p_ptr = p_alloc->p_data + offset,
            };
        }
        return (allocator_result_t) {
            .err_msg = "Allocator failed to resize memory; \"realloc\" failed and returned NULL",
            .p_ptr = p_alloc->p_data,
        };
    }
    return allocate_memory(p_alloc, size);
}

allocator_result_t resize_insert_memory(allocator_t* p_alloc, usize insert_size, usize insert_pos) {
    allocator_result_t res = resize_memory(p_alloc, p_alloc->size + insert_size);
    if (p_alloc->size == insert_pos || res.err_msg == NULL) {
        return res;
    }
    const usize full_size = p_alloc->size + insert_size;
    b8 copyed = memcpy((char*)p_alloc->p_data + (insert_pos + insert_size),
                       (char*)p_alloc->p_data + insert_pos, insert_size) != NULL;
    if (!copyed) {
        return (allocator_result_t) {
            .err_msg = "Failed to insert chunk of memory into allocation; \"memcpy\" failed and "
                       "returned NULL",
            .p_ptr = (char*)p_alloc->p_data + insert_pos,
        };
    }
    return (allocator_result_t) {
        .err_msg = ALLOCATOR_RESULT_PASSED,
        (char*)p_alloc->p_data + insert_pos,
    };
}
