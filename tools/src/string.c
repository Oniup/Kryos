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

#include "kryos-tools/string.h"
#include "kryos-tools/allocator.h"
#include "kryos-tools/debug.h"

#include <memory.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

usize get_string_length(const string_t* p_str) {
    return get_dynamic_allocation_size(p_str->p_cstr) - 1;
}

usize get_string_capacity(const string_t* p_str) {
    return get_dynamic_allocation_capacity(p_str->p_cstr);
}

b8 compare_string_cstr(const string_t* p_str, const char* p_cstr) {
    if (p_str != NULL && p_cstr != NULL) {
        usize str_len = get_string_length(p_str);
        usize cstr_len = strlen(p_cstr);
        if (str_len == cstr_len) {
            return strncmp(p_str->p_cstr, p_cstr, str_len) == 0;
        }
    }
    return false;
}

b8 compare_string(const string_t* p_str1, const string_t* p_str2) {
    if (p_str1 != NULL && p_str2 != NULL) {
        usize str1_len = get_string_length(p_str1);
        usize str2_len = get_string_length(p_str2);
        if (str1_len == str2_len) {
            return strncmp(p_str1->p_cstr, p_str2->p_cstr, str1_len) == 0;
        }
    }
    return false;
}

string_t create_string_cstr(const char* p_cstr) {
    if (p_cstr == NULL) {
        return EMPTY_STRING;
    }
    usize len = strlen(p_cstr);
    allocated_memory_result_t res = create_dynamic_allocation(len + 1);
    ASSERT(res.err_msg == NO_ALLOCATED_MEMORY_ERROR,
           "Failed to create string from cstr ('%s') due to allocator error: %s", p_cstr,
           res.err_msg);

    string_t str = {.p_cstr = (char*)res.p_data};
    errno_t err = memcpy_s(str.p_cstr, get_string_length(&str), p_cstr, len);
    if (err != 0) {
        ERROR("Failed to create string from cstr ('%s): memcpy_s err returned %d", p_cstr,
              err);
        destroy_dynamic_allocation(&str);
        return EMPTY_STRING;
    }

    str.p_cstr[len] = '\0';
    return str;
}

string_t create_string(const string_t* p_str) {
    if (p_str == NULL) {
        return EMPTY_STRING;
    }
    usize len = get_string_length(p_str);
    allocated_memory_result_t res = create_dynamic_allocation(len + 1);
    if (res.err_msg != NO_ALLOCATED_MEMORY_ERROR) {
        ERROR("Failed to create string from string ('%s'): string", p_str->p_cstr,
              res.err_msg);
        return EMPTY_STRING;
    }
    string_t str = {.p_cstr = (char*)res.p_data};
    errno_t err = memcpy_s(str.p_cstr, get_string_length(&str), p_str->p_cstr, len);
    if (err != 0) {
        ERROR(
            "Failed to create string from string ('%s'): memcpy_s failed and error code "
            "resulted in %d",
            p_str->p_cstr, err);
        destroy_string(&str);
        return EMPTY_STRING;
    }
    str.p_cstr[len] = '\0';
    return str;
}

string_t create_string_format(const char* p_fmt, ...) {
    if (p_fmt == NULL) {
        return EMPTY_STRING;
    }
    char buf[MAX_COPY_TMP_BUF_SIZE];
    va_list args;
    va_start(args, p_fmt);
    errno_t err = vsprintf_s(buf, MAX_COPY_TMP_BUF_SIZE, p_fmt, args);
    if (err < 0) {
        ERROR("Failed to create string using format '%s': vprintf_s error result %d",
              p_fmt, err);
        return EMPTY_STRING;
    }
    va_end(args);

    usize len = strlen(buf);
    allocated_memory_result_t res = create_dynamic_allocation(len + 1);
    if (res.err_msg != NO_ALLOCATED_MEMORY_ERROR) {
        ERROR("Failed to create string using format '%s': %s", p_fmt, res.err_msg);
        return EMPTY_STRING;
    }
    string_t str = {.p_cstr = res.p_data};
    err = memcpy_s(str.p_cstr, get_string_length(&str), buf, len);
    if (err != 0) {
        ERROR("Failed to create string: memcpy_s error code returned %d", err);
        destroy_dynamic_allocation(str.p_cstr);
        return EMPTY_STRING;
    }

    str.p_cstr[len] = '\0';
    return str;
}

void destroy_string(string_t* p_str) {
    destroy_dynamic_allocation(p_str->p_cstr);
    p_str->p_cstr = NULL;
}

b8 set_string(string_t* p_str, const string_t* p_src) {
    usize len = get_string_length(p_str);
    usize src_len = get_string_length(p_src);
    allocated_memory_result_t res = resize_dynamic_allocation(p_str->p_cstr, src_len + 1);
    if (res.err_msg != NO_ALLOCATED_MEMORY_ERROR) {
        ERROR("Failed to resize destination string of length %zu to %zu: %s", len,
              src_len, res.err_msg);
        return false;
    }
    p_str->p_cstr = (char*)res.p_data;
    errno_t err =
        memcpy_s(p_str->p_cstr, get_string_length(p_str), p_src->p_cstr, src_len);
    if (err != 0) {
        ERROR("Failed to copy string: memcpy_s error code returned %d", err);
        return false;
    }
    p_str->p_cstr[src_len] = '\0';
    return true;
}

b8 set_string_cstr(string_t* p_str, const char* p_src) {
    usize len = get_string_length(p_str);
    usize src_len = strlen(p_src);
    allocated_memory_result_t res = resize_dynamic_allocation(p_str->p_cstr, src_len + 1);
    if (res.err_msg != NO_ALLOCATED_MEMORY_ERROR) {
        ERROR("Failed to set string to cstr '%s'. String length needs to %zu -> %zu: %s",
              p_src, len, src_len, res.err_msg);
        return false;
    }
    p_str->p_cstr = (char*)res.p_data;
    errno_t err = memcpy_s(p_str->p_cstr, get_string_length(p_str), p_src, src_len);
    if (err != 0) {
        ERROR("Failed to copy string: memcpy_s error code returned %d", err);
        return false;
    }
    p_str->p_cstr[src_len] = '\0';
    return true;
}

b8 append_string(string_t* p_str, const string_t* p_src) {
    usize old_len = get_string_length(p_str);
    usize src_len = get_string_length(p_src);
    if (src_len > 0) {
        allocated_memory_result_t res =
            resize_dynamic_allocation(p_str->p_cstr, old_len + src_len);
        if (res.err_msg != NO_ALLOCATED_MEMORY_ERROR) {
            ERROR("Failed to append string '%s': %s", p_src->p_cstr, res.err_msg);
            return false;
        }
        p_str->p_cstr = (char*)res.p_data;
        errno_t err =
            memcpy_s(p_str->p_cstr + old_len, get_string_length(p_str) - old_len,
                     p_src->p_cstr, src_len);
        if (err != 0) {
            ERROR("Failed to append string '%s': memcpy_s failed, error resulted in %d",
                  p_str->p_cstr, err);
            return false;
        }
        p_str->p_cstr[get_string_length(p_str)] = '\0';
    }
    return true;
}

b8 append_string_cstr(string_t* p_str, const char* p_src) {
    usize old_len = get_string_length(p_str);
    usize src_len = strlen(p_src);
    if (src_len > 0) {
        allocated_memory_result_t res = resize_dynamic_allocation(p_str->p_cstr, src_len);
        if (res.err_msg != NO_ALLOCATED_MEMORY_ERROR) {
            ERROR("Failed to append string '%s': %s", p_src, res.err_msg);
            return false;
        }
        p_str->p_cstr = (char*)res.p_data;
        errno_t err = memcpy_s(p_str->p_cstr + old_len,
                               get_string_length(p_str) - old_len, p_src, src_len);
        if (err != 0) {
            ERROR("Failed to append string '%s': memcpy_s failed, error resulted in %d",
                  p_str->p_cstr, err);
            return false;
        }
        p_str->p_cstr[get_string_length(p_str)] = '\0';
    }
    return true;
}

b8 append_string_list(string_t* p_str, const string_t* p_list, usize count) {
    for (usize i = 0; i < count; i++) {
        b8 res = append_string(p_str, &p_list[i]);
        if (!res) {
            return false;
        }
    }
    return true;
}

b8 append_string_cstr_list(string_t* p_str, const char** p_list, usize count) {
    for (usize i = 0; i < count; i++) {
        b8 res = append_string_cstr(p_str, p_list[i]);
        if (!res) {
            return false;
        }
    }
    return true;
}

b8 format_string(string_t* p_str, const char* p_fmt, ...) {
    char buf[MAX_COPY_TMP_BUF_SIZE];
    va_list args;
    va_start(args, p_fmt);
    errno_t err = vsprintf_s(buf, MAX_COPY_TMP_BUF_SIZE, p_fmt, args);
    if (err < 0) {
        ERROR("Failed to format string using '%s': vprintf_s error result %d", p_fmt,
              err);
        return false;
    }
    va_end(args);
    usize buf_len = strlen(buf);
    allocated_memory_result_t res = resize_dynamic_allocation(p_str->p_cstr, buf_len);
    if (res.err_msg != NO_ALLOCATED_MEMORY_ERROR) {
        ERROR("Failed to format string using '%s': %s", p_fmt, res.err_msg);
        return false;
    }
    p_str->p_cstr = (char*)res.p_data;
    err = memcpy_s(p_str->p_cstr, get_string_length(p_str), buf, buf_len);
    if (err != 0) {
        ERROR("Failed to format string using '%s': memcpy_s failed and error code "
              "resulted in %d",
              p_fmt, err);
        return false;
    }
    p_str->p_cstr[get_string_length(p_str)] = '\0';
    return true;
}
