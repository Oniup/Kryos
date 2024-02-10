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

/// @brief Dynamic memory allocator structure.
typedef struct allocator {
    /// @brief Pointer to allocated memory
    void* p_data;
    /// @brief Allocation size in bytes
    usize size;
} allocator_t;

/// @brief Returned result after calling any function that might fail related to the allocator
/// object
typedef struct allocator_result {
    /// @brief NULL if there is no error, otherwise is a compile time string of
    /// describing error
    const char* err_msg;
    /// @brief Pointer to modified data
    void* p_ptr;
} allocator_result_t;

/// @brief Initializes allocator object and allocates memory of given size.
///
/// @param `size` The size of allocation block in bytes
///
/// @return Newly created allocator, will need to destroy manually by calling `deinit_allocator`
KRYAPI allocator_t init_allocator(usize size);

/// @brief Destroys/releases the given allocated memory.
///
/// @param `p_alloc` Pointer to allocator of target memory to be destroyed
KRYAPI void deinit_allocator(allocator_t* p_alloc);

/// @brief Allocate memory of given size into allocator.
/// @warning Does not free existing data that is already being handled by allocator and will cause a
/// memory leak if not released beforehand
///
/// @param `p_alloc` Pointer to allocator
///
/// @result Result structure, if `err_msg` is NULL then allocation was successful, otherwise will
/// provided a compile time string describing the error
KRYAPI allocator_result_t allocate_memory(allocator_t* p_alloc, usize size);

/// @brief Resize allocated memory to new given size
///
/// @param `p_alloc` Pointer to allocator with target memory to be resized
/// @param `resize` New size in bytes
///
/// @result Result structure, if `err_msg` is NULL then allocation was successful, otherwise will
/// provided a compile time string describing the error
KRYAPI allocator_result_t resize_memory(allocator_t* p_alloc, usize resize);

/// @brief Resize allocated memory to new given size and offset existing initialised data at insert
/// position by insert size. This enables new data to be initialized and inserted
///
/// @param `p_alloc` Pointer to allocator with target memory to be resized
/// @param `insert_size` Insertion size in bytes
/// @param `insert_pos` Offset that will be applied to pointer indicating where the insert should
/// start
///
/// @result Result structure, if `err_msg` is NULL then allocation was successful, otherwise will
/// provided a compile time string describing the error
KRYAPI allocator_result_t resize_insert_memory(allocator_t* p_alloc, usize insert_size,
                                               usize insert_pos);

#ifdef __cplusplus
}
#endif
#endif
