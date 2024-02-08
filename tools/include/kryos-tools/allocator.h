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
#ifdef __cplusplus
extern "C" {
#endif

#include "kryos-tools/defines.h"

#define ALLOCATOR_RESULT_PASSED NULL

typedef struct allocator {
    void* p_data;
    usize size;
} allocator_t;

typedef struct allocator_result {
    const char* err_msg;
    void* p_ptr;
} allocator_result_t;

KRYAPI void deinit_allocator(allocator_t* alloc);
KRYAPI allocator_t init_allocator(usize size);

KRYAPI allocator_result_t allocate_memory(allocator_t* alloc, usize size);
KRYAPI allocator_result_t resize_memory(allocator_t* alloc, usize resize);
KRYAPI allocator_result_t resize_insert_memory(allocator_t* alloc, usize insert_size,
                                               usize insert_pos);

#ifdef __cplusplus
}
#endif
#endif
