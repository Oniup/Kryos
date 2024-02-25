/// ------------------------------------------------------------------------ ///
/// This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine) ///
/// @file string.h                                                           ///
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

#ifndef KRYOS__TOOLS_CONTAINERS__STRING_H
#define KRYOS__TOOLS_CONTAINERS__STRING_H
#ifdef __cplusplus
extern "C" {
#endif

#include "kryos-tools/defines.h"

#define EMPTY_STRING (string_t) {.p_cstring = NULL};
#define MAX_COPY_TMP_BUFFER_SIZE 10000

// typedef struct string {
//     char* p_cstring;
// } string_t;
//
// KRYAPI usize get_string_length(const string_t* p_string);
// KRYAPI usize get_string_capacity(const string_t* p_string);
//
// KRYAPI b8 compare_string_cstring(const string_t* p_string, const char* p_cstring);
// KRYAPI b8 compare_string(const string_t* p_string1, const string_t* p_string2);
//
// KRYAPI string_t create_string_cstring(const char* p_cstring);
// KRYAPI string_t create_string(const string_t* string);
// KRYAPI string_t create_string_format(const char* p_format, ...);
//
// KRYAPI void destroy_string(string_t* p_string);
//
// KRYAPI b8 set_string(string_t* p_string, const string_t* p_source);
// KRYAPI b8 set_string_cstring(string_t* p_string, const char* p_source);
//
// KRYAPI b8 append_string(string_t* p_string, const string_t* p_source);
// KRYAPI b8 append_string_cstring(string_t* p_string, const char* p_source);
// KRYAPI b8 append_string_array(string_t* p_string, const string_t* p_array, usize count);
// KRYAPI b8 append_string_cstring_array(string_t* p_string, const char** p_array, usize count);
//
// KRYAPI b8 format_string(string_t* p_string, const char* p_format, ...);
//
#ifdef __cplusplus
}
#endif
#endif
