/// ------------------------------------------------------------------------ ///
/// This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine) ///
/// @file framework.c                                                        ///
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

#include "kryos-tests/framework.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static global_test_options_t g_opts = {
    .ansi_color = true,
};

void intl_print_message(const char* p_ansi_color, const char* p_format, ...);

b8 execute_tests(const char* p_title, usize count, test_t* p_tests) {
    intl_print_message(TEST_TITLE_ANSI_COLOR,
                       "%s\n-------------------------------------------------\n", p_title);
    usize tests_passed = false;
    for (usize i = 0; i < count; i++) {
        if (p_tests[i].test != NULL) {
            test_output_t result = {
                .message = "\0",
                .pass = true,
            };
            p_tests[i].test(&result);
            print_test_output(p_tests[i].p_name, &result, i, count, &tests_passed);
        } else {
            intl_print_message(TEST_FAILED_ANSI_COLOR, "TEST '%s' HAS NO TEST FUNCTION\n",
                               p_tests->p_name);
        }
    }
    if (tests_passed == count) {
        printf("%zu out of %zu passed\n", tests_passed, count);
        return true;
    }
    printf("%zu out of %zu passed\n", tests_passed, count);
    return false;
}

void print_test_output(const char* p_name, test_output_t* p_output, usize index, usize total_count,
                       usize* p_tests_passed) {
    const char* format = "%s%s%s%s%s %u/%u";
    const char* ansi_color = TEST_FAILED_ANSI_COLOR;
    if (p_output->pass) {
        ansi_color = TEST_PASS_ANSI_COLOR;
        *p_tests_passed = *p_tests_passed + 1;
    }

    printf(format, DEBUG_ANSI_PREFIX, ansi_color, DEBUG_ANSI_SUFIX, p_name, DEBUG_ANSI_RESET,
           index + 1, total_count);
    if (strlen(p_output->message) > 0) {
        printf(" => %s", p_output->message);
    }
    printf("\n");
}

void set_test_output_message(test_output_t* p_output, const char* p_format, ...) {
    va_list args;
    va_start(args, p_format);
    set_test_output_message_v(p_output, p_format, args);
    va_end(args);
}

void set_test_output_message_v(test_output_t* p_output, const char* p_format, va_list args) {
    vsprintf_s(p_output->message, MAX_TEST_OUTPUT_MESSAGE_SIZE, p_format, args);
}

void intl_print_message(const char* p_ansi_color, const char* p_format, ...) {
    va_list args;
    va_start(args, p_format);
    int result;
    if (g_opts.ansi_color && p_ansi_color[0] != TEST_TEXT_ANSI_COLOR) {
        printf("%s%s%s", DEBUG_ANSI_PREFIX, p_ansi_color, DEBUG_ANSI_SUFIX);
        result = vprintf_s(p_format, args);
        printf("%s", DEBUG_ANSI_RESET);
    } else {
        result = vprintf_s(p_format, args);
    }
    va_end(args);
    if (result < 0) {
        printf("Failed to print test results. va_list args are incorrect and cased vprintf_s to "
               "fail\n");
    }
}

global_test_options_t* get_global_test_options() {
    return &g_opts;
}
