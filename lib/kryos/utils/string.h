/**
 * @file string.h
 *
 * This file is part of the Kryos Engine (See AUTHORS.md)
 * GitHub Repository: https://github.com/Oniup/kryos
 *
 * @copyright
 * Copyright (c) 2023-present Oniup (https://github.com/Oniup/)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef KRYOS__UTILS__STRING_H_
#define KRYOS__UTILS__STRING_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>

#define KRY_STR_MAX_VSPRINTF_BUF_SIZE 2048

typedef struct kry_string_meta {
  size_t len;
  size_t cap;
} kry_string_meta_t;

typedef char* kry_string_t;

void kry_string_destroy(kry_string_t str);
kry_string_meta_t* kry_string_meta(kry_string_t str);

size_t kry_string_len(kry_string_t str);
size_t kry_string_capacity(kry_string_t str);

kry_string_t kry_string_resize_cap(kry_string_t str, size_t cap);

kry_string_t kry_string_create(const char* fmt, ...);
kry_string_t kry_string_append(kry_string_t dest, const char* fmt, ...);
kry_string_t kry_string_copy(kry_string_t dest, const char* fmt, ...);

kry_string_t kry_string_vcreate(const char* fmt, va_list args);
kry_string_t kry_string_vcopy(kry_string_t dest, const char* fmt, va_list args);
kry_string_t kry_string_vappend(kry_string_t dest, const char* fmt,
                                va_list args);

#ifdef __cplusplus
}
#endif

#endif
