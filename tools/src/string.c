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

#include "kryos-tools/string.h"
#include "kryos-tools/debug.h"

#include <memory.h>
#include <stdio.h>
#include <string.h>

// void deinit_string(string_t* p_str) {
//     deinit_allocator(&p_str->allocator);
// }
//
// string_t init_string(const char* p_cstr) {
//     const usize len = strlen(p_cstr);
//     string_t str = {.allocator = init_allocator(len)};
//     errno_t err = memcpy_s(str.p_cstr, str.len, p_cstr, len);
//     ASSERT(err != 0, "Failed to init string: memcpy_s returned error code %d", err);
//     return str;
// }
//
// string_t clone_string(const string_t* p_src) {
//     string_t str = {.allocator = init_allocator(p_src->len)};
//     b8 cpy_res = memcpy(str.p_cstr, p_src->p_cstr, str.len) != NULL;
//     ASSERT(cpy_res, "String: Failed to copy; \"memcpy\" failed to and returned NULL");
//     str.p_cstr[str.len] = '\0';
//     return str;
// }
//
// b8 set_string(string_t* p_str, const string_t* p_src) {
//     return false;
// }
//
// b8 set_string_cstr(string_t* p_str, const char* p_src) {
//     return false;
// }
//
// b8 append_string(string_t* p_str, const string_t* p_src) {
//     return false;
// }
//
// b8 append_string_cstr(string_t* p_str, const char* p_src, usize len) {
//     return false;
// }
//
// b8 uppercase_string(string_t* p_str) {
//     return false;
// }
//
// b8 lowercase_string(string_t* p_str) {
//     return false;
// }
//
// b8 format_string(const char* p_fmt, ...) {
//     return false;
// }
//
// string_t clone_format_string(const char* p_fmt, ...) {
//     return (string_t) {.p_cstr = NULL};
// }
//
// b8 trim_string(string_t* p_str) {
//     if (p_str->allocator.p_data == NULL) {
//         return false;
//     }
//     if (p_str->p_cstr[0] == '\0') {
//         return true;
//     }
//     usize trailing_removed = 0;
//     usize leading_removed = 0;
//     // if (p_str->p_cstr[0] != '\0') {
//     // if (removed_count > 0) {
//     //     void* res =
//     //         memcpy(p_str->p_cstr, p_str->p_cstr + removed_leading, p_str->len - removed_count);
//     //     if (res == NULL) {
//     //         return false;
//     //     }
//     //     DEBUG("removed_count: %zu, curr len: %zu, new len: %zu", removed_count, p_str->len,
//     //           p_str->len - removed_count);
//     //     allocator_result_t result = resize_memory(&p_str->allocator, p_str->len - removed_count);
//     //     if (result.err_msg != NULL) {
//     //         ERROR("Failed to trim string: %s", result.err_msg);
//     //         return false;
//     //     }
//     // }
//     // }
//     return true;
// }
