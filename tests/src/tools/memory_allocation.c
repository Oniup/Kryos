/// ------------------------------------------------------------------------ ///
/// This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine) ///
/// @file memory_allocation.c                                                ///
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

#include "kryos-tests/tools/memory_allocation.h"
#include "kryos-tests/framework.h"
#include "kryos-tools/containers/allocator.h"

// NOTE: These tests are checking whether the program crashes with undefined behaviour or not
#define ITERATION_COUNT 50

void allocate_and_destroy(test_output_t* p_out) {
    for (usize i = 0; i < ITERATION_COUNT; i++) {
        allocated_memory_result_t result = create_dynamic_allocation(sizeof(i32));
        IS_EQUALS(result.error_message, NO_ERROR_MESSAGE, "%s", result.error_message);
        destroy_dynamic_allocation(result.p_data);
    }
}

void resize_capacity_and_size(test_output_t* p_out) {
    for (usize i = 0; i < ITERATION_COUNT; i++) {
        allocated_memory_result_t result = create_dynamic_allocation(sizeof(i32) * 10);
        IS_EQUALS(result.error_message, NO_ERROR_MESSAGE, "%s", result.error_message);
        i32* p_data = (i32*)result.p_data;

        result = resize_dynamic_allocation(p_data, sizeof(i32) * 20);
        IS_EQUALS(result.error_message, NO_ERROR_MESSAGE, "%s", result.error_message);
        p_data = (i32*)result.p_data;
        for (usize j = 0; j < 20; j++) {
            p_data[j] = j + 1;
        }

        result = resize_dynamic_allocation(p_data, sizeof(i32) * 5);
        IS_EQUALS(result.error_message, NO_ERROR_MESSAGE, "%s", result.error_message);
        p_data = (i32*)result.p_data;
        for (usize j = 0; j < 5; j++) {
            p_data[j] = j + 2;
        }

        destroy_dynamic_allocation(p_data);
    }
}

void memory_allocation_tests() {
    TEST_TABLE() {
        ADD_TEST(allocate_and_destroy),
        ADD_TEST(resize_capacity_and_size),
    };
    EXECUTE_TEST_TABLE("Memory Allocation");
}
