/// ------------------------------------------------------------------------------------------------
/// This file is part of os Engine (https://github.com/Oniup/osEngine)
/// @file framework.h
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

#ifndef KRYOS__TESTS__FRAMEWORK_H
#define KRYOS__TESTS__FRAMEWORK_H
#ifdef __cplusplus
extern "C" {
#endif

#include "kryos-tools/debug.h"
#include "kryos-tools/defines.h"

#include <stdarg.h>

#define TEST_CHECK(expr, ...)                \
    ({                                       \
        if (!(expr)) {                       \
            output.pass = false;             \
            output.set_message(__VA_ARGS__); \
            return;                          \
        }                                    \
    })

#define TEST_EQ(a, b, ...)                   \
    ({                                       \
        if ((a) != (b)) {                    \
            output.pass = false;             \
            output.set_message(__VA_ARGS__); \
            return;                          \
        }                                    \
    })

#define TEST_TITLE_ANSI_COL DEBUG_ANSI_FG_CYAN
#define TEST_PASS_ANSI_COL DEBUG_ANSI_FG_GREEN
#define TEST_FAILED_ANSI_COL DEBUG_ANSI_FG_RED
#define TEST_TEXT_ANSI_COL -1

#define TEST_MAX_OUTPUT_MSG_SIZE 2000

typedef struct {
    char msg[TEST_MAX_OUTPUT_MSG_SIZE];
    b8 pass;
} test_output_t;

typedef void (*PFN_test)(test_output_t* result);

typedef struct {
    const char* p_name;
    PFN_test test;
} test_t;

typedef struct global_test_options {
    b8 ansi_col;
} global_test_options_t;

global_test_options_t* get_global_test_options();

b8 execute_tests(const char* p_title, test_t* p_tests, usize count);
void print_test_output(const char* p_name, test_output_t* p_output, usize index, usize total,
                       usize* p_tests_passed);

void set_test_output_message(test_output_t* p_output, const char* p_fmt, ...);
void set_output_message_v(test_output_t* p_output, const char* p_fmt, va_list args);

#ifdef __cplusplus
}
#endif
#endif
