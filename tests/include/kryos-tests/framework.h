/* ------------------------------------------------------------------------ *
 * This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine) *
 * @file framework.h                                                        *
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

#ifndef KRYOS__TESTS__FRAMEWORK_H
#define KRYOS__TESTS__FRAMEWORK_H
#ifdef __cplusplus
extern "C" {
#endif

#include "kryos-tools/debug.h"
#include "kryos-tools/defines.h"
#include <stdarg.h>

#define TEST_TITLE_ANSI_COLOR DEBUG_ANSI_FG_CYAN
#define TEST_PASS_ANSI_COLOR DEBUG_ANSI_FG_GREEN
#define TEST_FAILED_ANSI_COLOR DEBUG_ANSI_FG_RED
#define TEST_TEXT_ANSI_COLOR -1

#define MAX_TEST_OUTPUT_MESSAGE_SIZE 2000
#define EXECUTE_PER_TEST_COUNT 5

#define CHECK_IF(expression, ...)                        \
    ({                                                   \
        if (!(expression)) {                             \
            p_out->pass = false;                         \
            set_test_output_message(p_out, __VA_ARGS__); \
            return;                                      \
        }                                                \
    })

#define IS_EQUALS(a, b, ...) CHECK_IF((a) == (b), __VA_ARGS__)
#define NOT_EQUALS(a, b, ...) CHECK_IF((a) != (b), __VA_ARGS__)

#define IS_NULL(a, ...) IS_EQUALS((a), NULL, __VA_ARGS__)
#define NOT_NULL(a, ...) NOT_EQUALS((a), NULL, __VA_ARGS__)

#define TEST_TABLE() test_t tests[] =

#define ADD_TEST(name) \
    { .p_name = #name, .test = name, }

#define EXECUTE_TEST_TABLE(table_name) \
    execute_tests(table_name, sizeof(tests) / sizeof(tests[0]), tests)

typedef struct test_output {
    char message[MAX_TEST_OUTPUT_MESSAGE_SIZE];
    b8 pass;
} test_output_t;

typedef void (*PFN_test)(test_output_t* result);

typedef struct test {
    const char* p_name;
    PFN_test test;
} test_t;

typedef struct global_test_options {
    b8 ansi_color;
} global_test_options_t;

global_test_options_t* get_global_test_options();

b8 execute_tests(const char* p_title, usize count, test_t* p_tests);
void print_test_output(const char* p_name, test_output_t* p_output, usize index, usize total,
                       usize* p_tests_passed);

void set_test_output_message(test_output_t* p_output, const char* p_format, ...);
void set_test_output_message_v(test_output_t* p_output, const char* p_format, va_list args);

#ifdef __cplusplus
}
#endif
#endif
