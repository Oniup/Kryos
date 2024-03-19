/* ------------------------------------------------------------------------ *
 * This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine) *
 * @file string.hpp                                                         *
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

#ifndef KRYOS__TOOLS_CONTAINERS__STRING_HPP
#define KRYOS__TOOLS_CONTAINERS__STRING_HPP

#include "kryos-tools/defines.hpp"
#include <string.h>

#define EMPTY_STRING (string_t) {.p_cstring = NULL, .length = 0};
#define MAX_COPY_TMP_BUFFER_SIZE 10000

typedef struct string {
    char* p_cstring;
    usize length;
} string_t;

string_t create_string(const char* p_format, ...);
void destroy_string(string_t* p_string);

string_t clone_string(const string_t* p_string);
void copy_string(string_t* p_string, const string_t* p_source);
void append_string(string_t* p_string, const char* p_appending, usize count);

usize find_string_substring(const string_t* p_string, const char* p_substring);
usize find_last_string_substring(const string_t* p_string, const char* p_substring);

bool compare_strings(const string_t* p_string1, const string_t* p_string2);
bool has_string_prefix(const string_t* p_string, const char* p_prefix);
bool has_string_suffix(const string_t* p_string, const char* p_suffix);

#endif
