/// ------------------------------------------------------------------------------------------------
/// This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine)
/// @file string.h
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

#ifndef KRYOS__TOOLS__STRING_H
#define KRYOS__TOOLS__STRING_H
#ifdef __cplusplus
extern "C" {
#endif

#define EMPTY_STRING (string_t) {.p_cstr = NULL};
#define MAX_COPY_TMP_BUF_SIZE 10000

#include "kryos-tools/defines.h"

typedef struct string {
    char* p_cstr;
} string_t;

KRYAPI usize get_string_length(const string_t* p_str);
KRYAPI usize get_string_capacity(const string_t* p_str);

KRYAPI b8 compare_string_cstr(const string_t* p_str, const char* p_cstr);
KRYAPI b8 compare_string(const string_t* p_str1, const string_t* p_str2);

KRYAPI string_t create_string_cstr(const char* p_cstr);
KRYAPI string_t create_string(const string_t* str);
KRYAPI string_t create_string_format(const char* p_fmt, ...);

KRYAPI void destroy_string(string_t* p_str);

KRYAPI b8 set_string(string_t* p_str, const string_t* p_src);
KRYAPI b8 set_string_cstr(string_t* p_str, const char* p_src);

KRYAPI b8 append_string(string_t* p_str, const string_t* p_src);
KRYAPI b8 append_string_cstr(string_t* p_str, const char* p_src);
KRYAPI b8 append_string_list(string_t* p_str, const string_t* p_list, usize count);
KRYAPI b8 append_string_cstr_list(string_t* p_str, const char** p_list, usize count);

KRYAPI b8 format_string(string_t* p_str, const char* p_fmt, ...);

#ifdef __cplusplus
}
#endif
#endif
