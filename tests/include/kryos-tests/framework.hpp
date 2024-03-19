/* ------------------------------------------------------------------------ *
 * This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine) *
 * @file framework.hpp                                                      *
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

#ifndef KRYOS__TESTS__FRAMEWORK_HPP
#define KRYOS__TESTS__FRAMEWORK_HPP

#include "kryos-tools/debug.hpp"
#include "kryos-tools/defines.hpp"
#include <stdarg.h>

#define TEST_TITLE_ANSI_COLOR DEBUG_ANSI_FG_CYAN
#define TEST_PASS_ANSI_COLOR DEBUG_ANSI_FG_GREEN
#define TEST_FAILED_ANSI_COLOR DEBUG_ANSI_FG_RED
#define TEST_TEXT_ANSI_COLOR -1

#define MAX_TEST_OUTPUT_MESSAGE_SIZE 2000
#define EXECUTE_PER_TEST_COUNT 5

#define CHECK_IF(expression, ...)                   \
    ({                                              \
        if (!(expression)) {                        \
            out.pass = false;                       \
            setTestOutputMessage(out, __VA_ARGS__); \
            return;                                 \
        }                                           \
    })

#define IS_EQUALS(a, b, ...) CHECK_IF((a) == (b), __VA_ARGS__)
#define NOT_EQUALS(a, b, ...) CHECK_IF((a) != (b), __VA_ARGS__)

#define IS_NULL(a, ...) IS_EQUALS((a), NULL, __VA_ARGS__)
#define NOT_NULL(a, ...) NOT_EQUALS((a), NULL, __VA_ARGS__)

#define TEST_TABLE() Test internal_tests[] =

#define ADD_TEST(test_ptr_func)                         \
    Test {                                              \
        .name = #test_ptr_func, .test = &test_ptr_func, \
    }

#define EXECUTE_TEST_TABLE(table_name) \
    executeTests(table_name, sizeof(internal_tests) / sizeof(internal_tests[0]), internal_tests)

struct TestOutput {
    char message[MAX_TEST_OUTPUT_MESSAGE_SIZE];
    bool pass;
};

typedef void (*TestFunc)(TestOutput& out);

struct Test {
    const char* name;
    TestFunc test;
};

struct GlobalTestOptions {
    bool ansi_color;

    static GlobalTestOptions& get_instance();
};

bool executeTests(const char* title, usize count, const Test* tests);
void printTestOutput(const char* name, const TestOutput& output, usize index, usize total,
                     usize& tests_passed);

void setTestOutputMessage(TestOutput& output, const char* format, ...);
void setTestOutputMessageV(TestOutput& output, const char* format, va_list args);

#endif
