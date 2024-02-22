/// ------------------------------------------------------------------------ ///
/// This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine) ///
/// @file string.c                                                           ///
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

#include "kryos-tests/tools/string.h"
#include "kryos-tests/framework.h"
#include <kryos-tools/containers/string.h>
#include <string.h>

#define HELLO_WORLD_CSTRING "Hello World!!!"
#define HELLO_WORLD_CSTRING_LENGTH 14

void creating(test_output_t* p_out) {
    string_t string = create_string_cstring(HELLO_WORLD_CSTRING);
    usize length = get_string_length(&string);
    IS_EQUALS(length, HELLO_WORLD_CSTRING_LENGTH, "Incorrect string length");
    CHECK_IF(strncmp(string.p_cstring, HELLO_WORLD_CSTRING, length) == 0,
             "Resulting string not correct");

    destroy_string(&string);
    IS_NULL(string.p_cstring, "After deinit, string should be NULL");
}

void get_length(test_output_t* p_out) {
    string_t string1 = create_string_cstring(HELLO_WORLD_CSTRING);
    IS_EQUALS(HELLO_WORLD_CSTRING_LENGTH, get_string_length(&string1),
              "Failed to get correct length");

    destroy_string(&string1);
}

void comparing(test_output_t* p_out) {
    string_t string1 = create_string_cstring(HELLO_WORLD_CSTRING);
    string_t string2 = create_string_cstring(HELLO_WORLD_CSTRING);
    string_t string3 = create_string_cstring("Different string"); // Different length and text
    string_t string4 = create_string_cstring("World Hello");      // Only different text

    IS_EQUALS(
        compare_string_cstring(&string1, HELLO_WORLD_CSTRING), true,
        "Failed to compare string to cstring. Resulted in not being the same when they should");
    IS_EQUALS(
        compare_string_cstring(&string2, HELLO_WORLD_CSTRING), true,
        "Failed to compare string to cstring. Resulted in not being the same when they should");
    IS_EQUALS(compare_string(&string1, &string2), true,
              "Failed to compare string to another string. Resulted in not being the same when "
              "they should");

    IS_EQUALS(compare_string(&string1, &string3), false,
              "Failed to compare string to another string. Resulted in being the same when should"
              "not they should");
    IS_EQUALS(compare_string(&string1, &string4), false,
              "Failed to compare string to another string. Resulted in being the same when should"
              "not they should");

    destroy_string(&string1);
    destroy_string(&string2);
    destroy_string(&string3);
    destroy_string(&string4);
}

void copying(test_output_t* p_out) {
    string_t string = create_string_cstring(HELLO_WORLD_CSTRING);
    usize length = get_string_length(&string);

    string_t copy = create_string(&string);
    IS_EQUALS(get_string_length(&copy), length,
              "Copy has incorrect string length (%zu), Should be &zu", get_string_length(&copy),
              length);
    CHECK_IF(compare_string(&string, &copy), "Copy string is not the same as original string");

    const char* overriding_cstring = "I hate C";
    usize overriding_cstring_length = strlen(overriding_cstring);
    b8 result = set_string_cstring(&string, overriding_cstring);
    IS_EQUALS(result, true, "set_string_cstr function failed and returned false");
    IS_EQUALS(get_string_length(&string), overriding_cstring_length,
              "Set string to cstr length (%zu) is not correct. Should be %zu",
              get_string_length(&string), overriding_cstring_length);
    CHECK_IF(compare_string_cstring(&string, overriding_cstring),
             "Set string to cstr resulting str is not correct");

    destroy_string(&string);
    destroy_string(&copy);
}

void formatting(test_output_t* p_out) {
    string_t string = create_string_format("%s%s, %d", "Hello", " World", 420);
    CHECK_IF(compare_string_cstring(&string, "Hello World, 420"),
             "Failed to create string from format");

    b8 result = format_string(&string, "%d, %s", 420, "Hello World");
    IS_EQUALS(result, true, "Failed to format existing string as the function returned false");
    CHECK_IF(compare_string_cstring(&string, "420, Hello World"),
             "Failed to create string from format");

    destroy_string(&string);
}

void string_tests() {
    TEST_TABLE() {
        ADD_TEST(creating), ADD_TEST(get_length), ADD_TEST(comparing),
        ADD_TEST(copying),  ADD_TEST(formatting),
    };
    EXECUTE_TEST_TABLE("Tools: String");
}
