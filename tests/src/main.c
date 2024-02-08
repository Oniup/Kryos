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

#include "kryos-tests/framework.h"

void test_one(test_output_t* p_out) {
}

void test_two(test_output_t* p_out) {
}

void test_three(test_output_t* p_out) {
}

int main(int argc, char* p_argv[]) {
    test_t tests[3] = {
        {.p_name = "test_one", .test = test_one},
        {.p_name = "test_two", .test = test_two},
        {.p_name = "test_three", .test = test_three},
    };
    int code = execute_tests("Test framekwork unit testing", tests, 3);
    return code;
}
