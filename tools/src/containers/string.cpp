/* ------------------------------------------------------------------------ *
 * This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine) *
 * @file string.cpp                                                         *
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

#include "kryos-tools/containers/string.hpp"
#include "kryos-tools/containers/memory_allocator.hpp"
#include "kryos-tools/debug.hpp"
#include <memory.h>
#include <stdarg.h>
#include <stdio.h>

// string_t create_string(const char* p_format, ...) {
//     char buffer[MAX_COPY_TMP_BUFFER_SIZE];
//     va_list args;
//     va_start(args, p_format);
//     i32 error = vsnprintf(buffer, MAX_COPY_TMP_BUFFER_SIZE, p_format, args);
//     if (error < 0) {
//         ERROR("Failed to create string using format '%s': vsnprintf error result %d", p_format,
//               error);
//         return EMPTY_STRING;
//     }
//     va_end(args);
//     usize length = strlen(buffer);
//     allocated_memory_result_t result = createDynamicAllocation(length + 1);
//     if (result.error_message != NO_ERROR_MESSAGE) {
//         ERROR("Failed to create string using format '%s': %s", p_format, result.error_message);
//         return EMPTY_STRING;
//     }
//     string_t string = {
//         .p_cstring = (char*)result.p_data,
//         .length = length,
//     };
//     if (strncpy(string.p_cstring, buffer, length) == nullptr) {
//         ERROR("Failed to create string using format '%s': Failed to copy buffer string into heap "
//               "allocated string using strncpy",
//               p_format);
//         destroyHeapAllocation(string.p_cstring);
//         return EMPTY_STRING;
//     }
//     string.p_cstring[length] = '\0';
//     return string;
// }
//
// void destroy_string(string_t* p_string) {
//     destroyHeapAllocation(p_string->p_cstring);
//     p_string->p_cstring = nullptr;
//     p_string->length = 0;
// }
//
// string_t clone_string(const string_t* p_string) {
//     if (p_string == nullptr || p_string->p_cstring == nullptr) {
//         return EMPTY_STRING;
//     }
//     allocated_memory_result_t result = createDynamicAllocation(p_string->length + 1);
//     if (result.error_message != NO_ERROR_MESSAGE) {
//         ERROR("Failed to clone string '%s': %s", p_string->p_cstring, result.error_message);
//         return EMPTY_STRING;
//     }
//     string_t string = {
//         .p_cstring = (char*)result.p_data,
//         .length = p_string->length,
//     };
//     if (strncpy(string.p_cstring, p_string->p_cstring, p_string->length) == nullptr) {
//         ERROR("Failed to clone string '%s': strncpy failed", p_string->p_cstring);
//         destroyHeapAllocation(string.p_cstring);
//         return EMPTY_STRING;
//     }
//     string.p_cstring[string.length] = '\0';
//     return string;
// }
//
// void copy_string(string_t* p_string, const string_t* p_source) {
//     if (p_source == nullptr || p_source->p_cstring == nullptr) {
//         return;
//     }
//     destroy_string(p_string);
//     *p_string = clone_string(p_source);
// }
//
// void append_string(string_t* p_string, const char* p_appending, usize count) {
// }
//
// usize find_string_substring(const string_t* p_string, const char* p_substring) {
//     return 0;
// }
//
// usize find_last_string_substring(const string_t* p_string, const char* p_substring) {
//     return 0;
// }
//
// bool compare_strings(const string_t* p_string1, const string_t* p_string2) {
//     return false;
// }
//
// bool has_string_prefix(const string_t* p_string, const char* p_prefix) {
//     return false;
// }
//
// bool has_string_suffix(const string_t* p_string, const char* p_suffix) {
//     return false;
// }

// usize get_string_length(const string_t* p_string) {
//     return get_dynamic_allocation_size(p_string->p_cstring) - 1;
// }
//
// usize get_string_capacity(const string_t* p_string) {
//     return get_dynamic_allocation_capacity(p_string->p_cstring);
// }
//
// bool compare_string_cstring(const string_t* p_string, const char* p_cstring) {
//     if (p_string != nullptr && p_cstring != nullptr) {
//         usize string_length = get_string_length(p_string);
//         usize cstring_length = strlen(p_cstring);
//         if (string_length == cstring_length) {
//             return strncmp(p_string->p_cstring, p_cstring, string_length) == 0;
//         }
//     }
//     return false;
// }
//
// bool compare_string(const string_t* p_string1, const string_t* p_string2) {
//     if (p_string1 != nullptr && p_string2 != nullptr) {
//         usize string1_length = get_string_length(p_string1);
//         usize string2_length = get_string_length(p_string2);
//         if (string1_length == string2_length) {
//             return strncmp(p_string1->p_cstring, p_string2->p_cstring, string1_length) == 0;
//         }
//     }
//     return false;
// }
//
// string_t create_string_cstring(const char* p_cstring) {
//     if (p_cstring == nullptr) {
//         return EMPTY_STRING;
//     }
//     usize length = strlen(p_cstring);
//     allocated_memory_result_t res = create_dynamic_allocation(length + 1);
//     ASSERT(res.error_message == NO_ERROR_MESSAGE,
//            "Failed to create string from cstr ('%s') due to allocator error: %s", p_cstring,
//            res.error_message);
//
//     string_t string = {.p_cstring = (char*)res.p_data};
//     errno_t error = memcpy_s(string.p_cstring, get_string_length(&string), p_cstring, length);
//     if (error != 0) {
//         ERROR("Failed to create string from cstr ('%s): memcpy_s error returned %d", p_cstring,
//               error);
//         destroy_dynamic_allocation(&string);
//         return EMPTY_STRING;
//     }
//
//     string.p_cstring[length] = '\0';
//     return string;
// }
//
// string_t create_string(const string_t* p_string) {
//     if (p_string == nullptr) {
//         return EMPTY_STRING;
//     }
//     usize length = get_string_length(p_string);
//     allocated_memory_result_t result = create_dynamic_allocation(length + 1);
//     if (result.error_message != NO_ERROR_MESSAGE) {
//         ERROR("Failed to create string from string ('%s'): string", p_string->p_cstring,
//               result.error_message);
//         return EMPTY_STRING;
//     }
//     string_t string = {.p_cstring = (char*)result.p_data};
//     errno_t error =
//         memcpy_s(string.p_cstring, get_string_length(&string), p_string->p_cstring, length);
//     if (error != 0) {
//         ERROR("Failed to create string from string ('%s'): memcpy_s failed and error code
//         resulted "
//               "in %d",
//               p_string->p_cstring, error);
//         destroy_string(&string);
//         return EMPTY_STRING;
//     }
//     string.p_cstring[length] = '\0';
//     return string;
// }
//
// string_t create_string_format(const char* p_format, ...) {
//     if (p_format == nullptr) {
//         return EMPTY_STRING;
//     }
//     char buffer[MAX_COPY_TMP_BUFFER_SIZE];
//     va_list args;
//     va_start(args, p_format);
//     errno_t error = vsprintf_s(buffer, MAX_COPY_TMP_BUFFER_SIZE, p_format, args);
//     if (error < 0) {
//         ERROR("Failed to create string using format '%s': vprintf_s error result %d", p_format,
//               error);
//         return EMPTY_STRING;
//     }
//     va_end(args);
//
//     usize length = strlen(buffer);
//     allocated_memory_result_t result = create_dynamic_allocation(length + 1);
//     if (result.error_message != NO_ERROR_MESSAGE) {
//         ERROR("Failed to create string using format '%s': %s", p_format, result.error_message);
//         return EMPTY_STRING;
//     }
//     string_t string = {.p_cstring = result.p_data};
//     error = memcpy_s(string.p_cstring, get_string_length(&string), buffer, length);
//     if (error != 0) {
//         ERROR("Failed to create string: memcpy_s error code returned %d", error);
//         destroy_dynamic_allocation(string.p_cstring);
//         return EMPTY_STRING;
//     }
//
//     string.p_cstring[length] = '\0';
//     return string;
// }
//
// void destroy_string(string_t* p_string) {
//     destroy_dynamic_allocation(p_string->p_cstring);
//     p_string->p_cstring = nullptr;
// }
//
// bool set_string(string_t* p_string, const string_t* p_source) {
//     usize length = get_string_length(p_string);
//     usize src_length = get_string_length(p_source);
//     allocated_memory_result_t result =
//         resize_dynamic_allocation(p_string->p_cstring, src_length + 1);
//     if (result.error_message != NO_ERROR_MESSAGE) {
//         ERROR("Failed to resize destination string of length %zu to %zu: %s", length, src_length,
//               result.error_message);
//         return false;
//     }
//     p_string->p_cstring = (char*)result.p_data;
//     errno_t error =
//         memcpy_s(p_string->p_cstring, get_string_length(p_string), p_source->p_cstring,
//         src_length);
//     if (error != 0) {
//         ERROR("Failed to copy string: memcpy_s error code returned %d", error);
//         return false;
//     }
//     p_string->p_cstring[src_length] = '\0';
//     return true;
// }
//
// bool set_string_cstring(string_t* p_string, const char* p_source) {
//     usize length = get_string_length(p_string);
//     usize source_length = strlen(p_source);
//     allocated_memory_result_t result =
//         resize_dynamic_allocation(p_string->p_cstring, source_length + 1);
//     if (result.error_message != NO_ERROR_MESSAGE) {
//         ERROR("Failed to set string to cstr '%s'. String length needs to %zu -> %zu: %s",
//         p_source,
//               length, source_length, result.error_message);
//         return false;
//     }
//     p_string->p_cstring = (char*)result.p_data;
//     errno_t err =
//         memcpy_s(p_string->p_cstring, get_string_length(p_string), p_source, source_length);
//     if (err != 0) {
//         ERROR("Failed to copy string: memcpy_s error code returned %d", err);
//         return false;
//     }
//     p_string->p_cstring[source_length] = '\0';
//     return true;
// }
//
// bool append_string(string_t* p_string, const string_t* p_src) {
//     usize old_len = get_string_length(p_string);
//     usize src_len = get_string_length(p_src);
//     if (src_len > 0) {
//         allocated_memory_result_t res =
//             resize_dynamic_allocation(p_string->p_cstring, old_len + src_len);
//         if (res.error_message != NO_ERROR_MESSAGE) {
//             ERROR("Failed to append string '%s': %s", p_src->p_cstring, res.error_message);
//             return false;
//         }
//         p_string->p_cstring = (char*)res.p_data;
//         errno_t err = memcpy_s(p_string->p_cstring + old_len, get_string_length(p_string) -
//         old_len,
//                                p_src->p_cstring, src_len);
//         if (err != 0) {
//             ERROR("Failed to append string '%s': memcpy_s failed, error resulted in %d",
//                   p_string->p_cstring, err);
//             return false;
//         }
//         p_string->p_cstring[get_string_length(p_string)] = '\0';
//     }
//     return true;
// }
//
// bool append_string_cstring(string_t* p_string, const char* p_src) {
//     usize old_len = get_string_length(p_string);
//     usize src_len = strlen(p_src);
//     if (src_len > 0) {
//         allocated_memory_result_t res = resize_dynamic_allocation(p_string->p_cstring, src_len);
//         if (res.error_message != NO_ERROR_MESSAGE) {
//             ERROR("Failed to append string '%s': %s", p_src, res.error_message);
//             return false;
//         }
//         p_string->p_cstring = (char*)res.p_data;
//         errno_t err = memcpy_s(p_string->p_cstring + old_len, get_string_length(p_string) -
//         old_len,
//                                p_src, src_len);
//         if (err != 0) {
//             ERROR("Failed to append string '%s': memcpy_s failed, error resulted in %d",
//                   p_string->p_cstring, err);
//             return false;
//         }
//         p_string->p_cstring[get_string_length(p_string)] = '\0';
//     }
//     return true;
// }
//
// bool append_string_array(string_t* p_string, const string_t* p_list, usize count) {
//     for (usize i = 0; i < count; i++) {
//         bool res = append_string(p_string, &p_list[i]);
//         if (!res) {
//             return false;
//         }
//     }
//     return true;
// }
//
// bool append_string_cstring_array(string_t* p_string, const char** p_list, usize count) {
//     for (usize i = 0; i < count; i++) {
//         bool res = append_string_cstring(p_string, p_list[i]);
//         if (!res) {
//             return false;
//         }
//     }
//     return true;
// }
//
// bool format_string(string_t* p_string, const char* p_format, ...) {
//     char buffer[MAX_COPY_TMP_BUFFER_SIZE];
//     va_list args;
//     va_start(args, p_format);
//     errno_t error = vsprintf_s(buffer, MAX_COPY_TMP_BUFFER_SIZE, p_format, args);
//     if (error < 0) {
//         ERROR("Failed to format string using '%s': vprintf_s error result %d", p_format, error);
//         return false;
//     }
//     va_end(args);
//     usize buffer_length = strlen(buffer);
//     allocated_memory_result_t result =
//         resize_dynamic_allocation(p_string->p_cstring, buffer_length);
//     if (result.error_message != NO_ERROR_MESSAGE) {
//         ERROR("Failed to format string using '%s': %s", p_format, result.error_message);
//         return false;
//     }
//     p_string->p_cstring = (char*)result.p_data;
//     error = memcpy_s(p_string->p_cstring, get_string_length(p_string), buffer, buffer_length);
//     if (error != 0) {
//         ERROR("Failed to format string using '%s': memcpy_s failed and error code resulted in
//         %d",
//               p_format, error);
//         return false;
//     }
//     p_string->p_cstring[get_string_length(p_string)] = '\0';
//     return true;
// }
