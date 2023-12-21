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

#ifndef KRYOS__CONTAINERS__STRING_H_
#define KRYOS__CONTAINERS__STRING_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>

#define KSTR_MAX_VSPRINTF_BUF_SIZE 2048

typedef struct string_header {
  size_t len;
  size_t cap;
} string_header_t;

typedef char* string_t;

void string_destroy(string_t str);
string_header_t* string_header(string_t str);

size_t string_len(string_t str);
size_t string_cap(string_t str);

string_t string_resize_cap(string_t str, size_t cap);

string_t string_create(const char* fmt, ...);
string_t string_append(string_t dest, const char* fmt, ...);
string_t string_copy(string_t dest, const char* fmt, ...);

string_t string_vcreate(const char* fmt, va_list args);
string_t string_vcopy(string_t dest, const char* fmt, va_list args);
string_t string_vappend(string_t dest, const char* fmt, va_list args);

#ifdef __cplusplus
}
#endif

#endif
