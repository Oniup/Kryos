/**
 * @file console.h
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

#ifndef KRYOS__CORE__CONSOLE_H_
#define KRYOS__CORE__CONSOLE_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "utils/utils.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define KRY_COL_LOG(level, col, fmt, ...) \
  kry_console_log(level, __FILE__, __LINE__, col, fmt, __VA_ARGS__)

#define KRY_COL_INFO(col, fmt, ...) \
  KRY_COL_LOG(KRY_CONSOLE_SEVERITY_INFO_BIT, col, fmt, __VA_ARGS__)

#define KRY_COL_DEBUG(col, fmt, ...) \
  KRY_COL_LOG(KRY_CONSOLE_SEVERITY_DEBUG_BIT, col, fmt, __VA_ARGS__)

#define KRY_COL_TRACE(col, fmt, ...) \
  KRY_COL_LOG(KRY_CONSOLE_SEVERITY_TRACE_BIT, col, fmt, __VA_ARGS__)

#define KRY_COL_WARN(col, fmt, ...) \
  KRY_COL_LOG(KRY_CONSOLE_SEVERITY_WARN_BIT, col, fmt, __VA_ARGS__)

#define KRY_COL_ERROR(col, fmt, ...) \
  KRY_COL_LOG(KRY_CONSOLE_SEVERITY_ERROR_BIT, col, fmt, __VA_ARGS__)

#define KRY_COL_FATAL(col, fmt, ...) \
  KRY_COL_LOG(KRY_CONSOLE_SEVERITY_FATAL_BIT, col, fmt, __VA_ARGS__)

// Default log macros

#define KRY_INFO(fmt, ...) KRY_COL_INFO(KRY_ANSI_COL_GREEN, fmt, __VA_ARGS__)

#define KRY_DEBUG(fmt, ...) KRY_COL_DEBUG(KRY_ANSI_COL_CYAN, fmt, __VA_ARGS__)

#define KRY_TRACE(fmt, ...) KRY_COL_TRACE(KRY_ANSI_COL_GREY, fmt, __VA_ARGS__)

#define KRY_WARN(fmt, ...) KRY_COL_WARN(KRY_ANSI_COL_YELLOW, fmt, __VA_ARGS__)

#define KRY_ERROR(fmt, ...) KRY_COL_ERROR(KRY_ANSI_COL_RED, fmt, __VA_ARGS__)

#define KRY_FATAL(fmt, ...) \
  KRY_COL_FATAL(KRY_ANSI_COL_BHL_RED, fmt, __VA_ARGS__)

#ifndef NDEBUG
#define KRY_ASSERT(expression, fmt, ...) \
  (void)((!!(expression)) || (KRY_FATAL(fmt, __VA_ARGS__), 0))
#else
#define KRY_ASSERT(expression, fmt, ...)
#endif

typedef enum kry_console_severity_bit {
  KRY_CONSOLE_SEVERITY_NONE_BIT = 0,
  KRY_CONSOLE_SEVERITY_INFO_BIT = 1 << 1,
  KRY_CONSOLE_SEVERITY_TRACE_BIT = 1 << 2,
  KRY_CONSOLE_SEVERITY_DEBUG_BIT = 1 << 3,
  KRY_CONSOLE_SEVERITY_WARN_BIT = 1 << 4,
  KRY_CONSOLE_SEVERITY_ERROR_BIT = 1 << 5,
  KRY_CONSOLE_SEVERITY_FATAL_BIT = 1 << 6,
} kry_console_severity_bit_t;

typedef int kry_console_filter_t;

const char* kry_console_severity_to_string(kry_console_severity_bit_t lv);

typedef void (*kry_console_callback_t)(kry_console_severity_bit_t lv,
                                       const char* file, int line,
                                       const char* col, const char* fmt,
                                       va_list args);

typedef struct kry_console {
  const char* output_file;
  kry_console_filter_t filter;
  kry_console_callback_t callback;
} kry_console_t;

void kry_console_log(kry_console_severity_bit_t lv, const char* file, int line,
                     const char* col, const char* fmt, ...);

void kry_console_log_v(kry_console_severity_bit_t lv, const char* file,
                       int line, const char* col, const char* fmt,
                       va_list args);

#ifdef __cplusplus
}
#endif
#endif
