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

#define HELLO_WORLD_CSTR "Hello World!!!"
#define HELLO_WORLD_CSTR_LEN 14

void creating(test_output_t* p_out) {
    string_t str = create_string_cstr(HELLO_WORLD_CSTR);
    usize len = get_string_length(&str);
    IS_EQUALS(len, HELLO_WORLD_CSTR_LEN, "Incorrect string length");
    CHECK_IF(strncmp(str.p_cstr, HELLO_WORLD_CSTR, len) == 0, "Resulting string not correct");

    destroy_string(&str);
    IS_NULL(str.p_cstr, "After deinit, string should be NULL");
}

void get_length(test_output_t* p_out) {
    string_t str1 = create_string_cstr(HELLO_WORLD_CSTR);
    IS_EQUALS(HELLO_WORLD_CSTR_LEN, get_string_length(&str1), "Failed to get correct length");

    destroy_string(&str1);
}

void comparing(test_output_t* p_out) {
    string_t str1 = create_string_cstr(HELLO_WORLD_CSTR);
    string_t str2 = create_string_cstr(HELLO_WORLD_CSTR);
    string_t str3 = create_string_cstr("Different string"); // Diff len and txt
    string_t str4 = create_string_cstr("World Hello");      // Only diff text

    IS_EQUALS(compare_string_cstr(&str1, HELLO_WORLD_CSTR), true,
              "Failed to compare string to cstr. Resulted in not being the same when they should");
    IS_EQUALS(compare_string_cstr(&str2, HELLO_WORLD_CSTR), true,
              "Failed to compare string to cstr. Resulted in not being the same when they should");
    IS_EQUALS(compare_string(&str1, &str2), true,
              "Failed to compare string to another string. Resulted in not being the same when "
              "they should");

    IS_EQUALS(compare_string(&str1, &str3), false,
              "Failed to compare string to another string. Resulted in being the same when should"
              "not they should");
    IS_EQUALS(compare_string(&str1, &str4), false,
              "Failed to compare string to another string. Resulted in being the same when should"
              "not they should");

    destroy_string(&str1);
    destroy_string(&str2);
    destroy_string(&str3);
    destroy_string(&str4);
}

void copying(test_output_t* p_out) {
    string_t str = create_string_cstr(HELLO_WORLD_CSTR);
    usize len = get_string_length(&str);

    string_t cpy = create_string(&str);
    IS_EQUALS(get_string_length(&cpy), len, "Copy has incorrect string length (%zu), Should be &zu",
              get_string_length(&cpy), len);
    CHECK_IF(compare_string(&str, &cpy), "Copy string is not the same as original string");

    const char* overriding_cstr = "I hate C";
    usize overriding_cstr_len = strlen(overriding_cstr);
    b8 res = set_string_cstr(&str, overriding_cstr);
    IS_EQUALS(res, true, "set_string_cstr function failed and returned false");
    IS_EQUALS(get_string_length(&str), overriding_cstr_len,
              "Set string to cstr length (%zu) is not correct. Should be %zu",
              get_string_length(&str), overriding_cstr_len);
    CHECK_IF(compare_string_cstr(&str, overriding_cstr),
             "Set string to cstr resulting str is not correct");

    destroy_string(&str);
    destroy_string(&cpy);
}

void formatting(test_output_t* p_out) {
    string_t str = create_string_format("%s%s, %d", "Hello", " World", 420);
    CHECK_IF(compare_string_cstr(&str, "Hello World, 420"), "Failed to create string from format");

    b8 res = format_string(&str, "%d, %s", 420, "Hello World");
    IS_EQUALS(res, true, "Failed to format existing string as the function returned false");
    CHECK_IF(compare_string_cstr(&str, "420, Hello World"), "Failed to create string from format");

    destroy_string(&str);
}

void string_tests() {
    TEST_TABLE() {
        ADD_TEST(creating), ADD_TEST(get_length), ADD_TEST(comparing),
        ADD_TEST(copying),  ADD_TEST(formatting),
    };
    EXECUTE_TEST_TABLE("Tools: String");
}
