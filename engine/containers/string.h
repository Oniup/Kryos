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

#include "defines.h"

#include <stdarg.h>

#define KSTR_MAX_VSPRINTF_BUF_SIZE 2048

char* string_create(const char* fmt, ...);
char* string_append(char* dest, const char* fmt, ...);
char* string_copy(char* dest, const char* fmt, ...);

char* string_vcreate(const char* fmt, va_list args);
char* string_vcopy(char* dest, const char* fmt, va_list args);
char* string_vappend(char* dest, const char* fmt, va_list args);

#ifdef __cplusplus
}
#endif

#endif
