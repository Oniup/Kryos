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

#include "kryos-tools/allocator.h"
#include "kryos-tools/defines.h"

typedef struct string {
    allocator_t allocator;
    union {
        char* cstr;
        usize len;
    };
} string_t;

KRYAPI void deinit_string(string_t* str);
KRYAPI string_t init_string(const char* cstr);

KRYAPI string_t clone_string(const string_t* str);
KRYAPI b8 set_string(string_t* dest, const string_t* src);
KRYAPI b8 set_string_cstr(string_t* dest, const char* src);
KRYAPI b8 append_string(string_t* dest, const string_t* src);
KRYAPI b8 append_string_cstr(string_t* dest, const char* src, usize len);

KRYAPI string_t format_string(const char* fmt, ...);
KRYAPI string_t format_string_v(const char* fmt, va_list args);

KRYAPI b8 trim_string(string_t* str);

#ifdef __cplusplus
}
#endif
#endif
