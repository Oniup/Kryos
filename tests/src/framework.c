/// ------------------------------------------------------------------------------------------------
/// This file is part of os Engine (https://github.com/Oniup/osEngine)
/// @file framework.c
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

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static global_test_options_t g_opts = {
    .ansi_col = true,
};

void print_msg(const char* p_ansi_col, const char* p_fmt, ...) {
    va_list args;
    va_start(args, p_fmt);
    int res;
    if (g_opts.ansi_col && p_ansi_col[0] != TEST_TEXT_ANSI_COL) {
        printf("%s%s%s", DEBUG_ANSI_PREFIX, p_ansi_col, DEBUG_ANSI_SUFIX);
        res = vprintf_s(p_fmt, args);
        printf("%s", DEBUG_ANSI_RESET);
    } else {
        res = vprintf_s(p_fmt, args);
    }
    va_end(args);
    if (res < 0) {
        printf("Failed to print test results. va_list args are incorrect and cased vprintf_s to "
               "fail\n");
    }
}

global_test_options_t* get_global_test_options() {
    return &g_opts;
}

b8 execute_tests(const char* p_title, usize count, test_t* p_tests) {
    print_msg(TEST_TITLE_ANSI_COL, "%s\n-------------------------------------------------\n",
              p_title);
    usize tests_passed = false;
    for (usize i = 0; i < count; i++) {
        if (p_tests[i].test != NULL) {
            test_output_t result = {
                .msg = "\0",
                .pass = true,
            };
            p_tests[i].test(&result);
            print_test_output(p_tests[i].p_name, &result, i, count, &tests_passed);
        } else {
            print_msg(TEST_FAILED_ANSI_COL, "TEST '%s' HAS NO TEST FUNCTION\n", p_tests->p_name);
        }
    }
    if (tests_passed == count) {
        print_msg(TEST_PASS_ANSI_COL, "%zu out of %zu passed", tests_passed, count);
        return true;
    }
    print_msg(TEST_FAILED_ANSI_COL, "%zu out of %zu passed", tests_passed, count);
    return false;
}

void print_test_output(const char* p_name, test_output_t* p_output, usize index, usize total_count,
                       usize* p_tests_passed) {
    const char* fmt = "%s%s%s%s %s%s %u/%u";
    const char* ansi_col = TEST_FAILED_ANSI_COL;
    const char* icon = "";
    if (p_output->pass) {
        icon = "";
        ansi_col = TEST_PASS_ANSI_COL;
        *p_tests_passed = *p_tests_passed + 1;
    }

    printf(fmt, DEBUG_ANSI_PREFIX, ansi_col, DEBUG_ANSI_SUFIX, icon, p_name, DEBUG_ANSI_RESET,
           index + 1, total_count);
    if (strlen(p_output->msg) > 0) {
        printf(" => %s\n", p_output->msg);
    } else {
        printf("\n");
    }
}

void set_test_output_message(test_output_t* p_output, const char* p_fmt, ...) {
    va_list args;
    va_start(args, p_fmt);
    set_output_message_v(p_output, p_fmt, args);
    va_end(args);
}

void set_output_message_v(test_output_t* p_output, const char* p_fmt, va_list args) {
    vsprintf_s(p_output->msg, TEST_MAX_OUTPUT_MSG_SIZE, p_fmt, args);
}
