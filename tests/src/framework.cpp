/* ------------------------------------------------------------------------ *
 * This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine) *
 * @file framework.cpp                                                      *
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

#include "kryos-tests/framework.hpp"
#include <cstdarg>
#include <cstdio>
#include <cstring>

namespace internal {
void printMessage(const char* ansi_color, const char* format, ...) {
    va_list args;
    va_start(args, format);
    if (GlobalTestOptions::get_instance().ansi_color && ansi_color[0] != TEST_TEXT_ANSI_COLOR) {
        printf("%s%s%s", DEBUG_ANSI_PREFIX, ansi_color, DEBUG_ANSI_SUFIX);
        vprintf(format, args);
        printf("%s", DEBUG_ANSI_RESET);
    } else {
        vprintf(format, args);
    }
    va_end(args);
}
} // namespace internal

GlobalTestOptions& GlobalTestOptions::get_instance() {
    static GlobalTestOptions settings = {
        .ansi_color = true,
    };
    return settings;
}

bool executeTests(const char* title, usize count, const Test* tests) {
    internal::printMessage(TEST_TITLE_ANSI_COLOR,
                           "%s\n-------------------------------------------------\n", title);
    usize tests_passed = false;
    for (usize i = 0; i < count; i++) {
        if (tests[i].test != NULL) {
            TestOutput result = {
                .message = "\0",
                .pass = true,
            };
            for (usize j = 0; j < EXECUTE_PER_TEST_COUNT; j++) {
                tests[i].test(result);
            }
            printTestOutput(tests[i].name, result, i, count, tests_passed);
        } else {
            internal::printMessage(TEST_FAILED_ANSI_COLOR, "TEST '%s' HAS NO TEST FUNCTION\n",
                                   tests->name);
        }
    }
    if (tests_passed == count) {
        printf("%zu out of %zu passed\n", tests_passed, count);
        return true;
    }
    printf("%zu out of %zu passed\n", tests_passed, count);
    return false;
}

void printTestOutput(const char* name, const TestOutput& output, usize index, usize total_count,
                     usize& tests_passed) {
    const char* format = "%s%s%s%s%s %u/%u";
    const char* ansi_color = TEST_FAILED_ANSI_COLOR;
    if (output.pass) {
        ansi_color = TEST_PASS_ANSI_COLOR;
        tests_passed++;
    }

    printf(format, DEBUG_ANSI_PREFIX, ansi_color, DEBUG_ANSI_SUFIX, name, DEBUG_ANSI_RESET,
           index + 1, total_count);
    if (strlen(output.message) > 0) {
        printf(" => %s", output.message);
    }
    printf("\n");
}

void setTestOutputMessage(TestOutput& output, const char* format, ...) {
    va_list args;
    va_start(args, format);
    setTestOutputMessageV(output, format, args);
    va_end(args);
}

void setTestOutputMessageV(TestOutput& output, const char* format, va_list args) {
    vsnprintf(output.message, MAX_TEST_OUTPUT_MESSAGE_SIZE, format, args);
}
