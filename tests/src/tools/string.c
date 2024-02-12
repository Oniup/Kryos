/// ------------------------------------------------------------------------------------------------
/// This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine)
/// @file string.c
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

#include "kryos-tests/tools/string.h"
#include "kryos-tests/framework.h"

#include <kryos-tools/string.h>
#include <string.h>

// void creating_string(test_output_t* out) {
//     const char* cstr = "Hello World!!!";
//     const usize len = strlen(cstr);
//
//     string_t str = init_string(cstr);
//     IS_EQUALS(str.len, len, "Incorrect string length");
//     CHECK_IF(strncmp(str.p_cstr, cstr, str.len) == 0, "Resulting string not correct");
//
//     deinit_string(&str);
//     IS_NULL(str.p_cstr, "After deinit, string should be NULL");
// }
//
// void trim_leading_and_trailing_whitespaces(test_output_t* out) {
//     const char* correct = "Hello World!!!";
//     const usize correct_len = strlen(correct);
//     string_t trailing = init_string("Hello World!!!     ");
//     string_t leading = init_string("     Hello World!!!");
//     string_t both = init_string(" Hello World!!!            ");
//
//     trim_string(&trailing);
//     CHECK_IF(strncmp(trailing.p_cstr, correct, trailing.len) == 0, "Failed to trim trailing");
//
//     trim_string(&leading);
//     CHECK_IF(strncmp(leading.p_cstr, correct, trailing.len) == 0, "Failed to trim leading");
//
//     trim_string(&both);
//     CHECK_IF(strncmp(both.p_cstr, correct, trailing.len) == 0,
//              "Failed to trim both trailing and leading");
//
//     deinit_string(&trailing);
//     deinit_string(&leading);
//     deinit_string(&both);
//     IS_NULL(trailing.p_cstr, "After deinit, string should be NULL");
//     IS_NULL(leading.p_cstr, "After deinit, string should be NULL");
//     IS_NULL(both.p_cstr, "After deinit, string should be NULL");
// }
//
void execute_string_tests() {
    // TEST_TABLE() {
    //     ADD_TEST(creating_string),
    //     ADD_TEST(trim_leading_and_trailing_whitespaces),
    // };
    // EXECUTE_TEST_TABLE("Tools: String");
}
