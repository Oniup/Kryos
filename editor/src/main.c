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
#include <string.h>

int main(int argc, char* argv[]) {
    b8 first = true;
    const char* smaller_str = "Hello World!!!";
    const char* larger_str = "This is a langer string";
    for (usize i = 0; i < 100; i++) {
        allocated_memory_result_t res = create_dynamic_allocation(strlen(smaller_str) + 1);
        ASSERT(res.err_msg == NO_ALLOCATED_MEMORY_ERROR, "%s", res.err_msg);
        char* p_str = (char*)res.p_data;
        strncpy(p_str, smaller_str, strlen(smaller_str));
        p_str[strlen(smaller_str)] = '\0';

        if (first) {
            printf("created: %s\n", p_str);
        }

        res = resize_dynamic_allocation(p_str, strlen(larger_str) +
                                                   1); // Use the correct size for the resize
        ASSERT(res.err_msg == NO_ALLOCATED_MEMORY_ERROR, "%s", res.err_msg);
        p_str = (char*)res.p_data; // Update the pointer after the resize operation
        strncpy(p_str, larger_str, strlen(larger_str));
        p_str[strlen(larger_str)] = '\0';

        if (first) {
            printf("resized: %s\n", p_str);
        }

        destroy_dynamic_allocation(p_str);
        if (first) {
            first = false;
        }
    }
    printf("success");
    return 0;
}
