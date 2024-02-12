/// ------------------------------------------------------------------------------------------------
/// This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine)
/// @file main.c
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
#include "kryos-tools/debug.h"

#include <stdio.h>

int main(int argc, char* argv[]) {
    INFO("Information that might be useful to the user");
    TRACE("Not that important");
    WARN("Important message");
    DEBUG("Testing/debugging log");
    ERROR("Breaking issue, should be fixed %s", "as soon as possible");

    b8 first = true;
    for (usize i = 0; i < 100; i++) {
        allocated_memory_result_t create_result = create_dynamic_allocation(sizeof(usize) * 2);
        ASSERT(create_result.err_msg == NO_ALLOCATED_MEMORY_ERROR, create_result.err_msg);
        usize* p_data = (usize*)create_result.p_data;
        p_data[0] = 1;
        p_data[1] = 2;
        if (first) {
            for (usize j = 0; j < 2; j++) {
                printf("%zu ", p_data[j]);
            }
        }

        destroy_dynamic_allocation(p_data);
        if (first) {
            first = false;
        }
    }
    printf("\nsuccess");
    return 0;
}
