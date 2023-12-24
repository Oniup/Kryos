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

#include "defines.h"

#define KCOL_LOG(level, col, fmt, ...) \
  console_log(level, __FILE__, __LINE__, col, fmt, __VA_ARGS__)

#define KCOL_INFO(col, fmt, ...) \
  KCOL_LOG(CONSOLE_SEVERITY_INFO_BIT, col, fmt, __VA_ARGS__)

#define KCOL_DEBUG(col, fmt, ...) \
  KCOL_LOG(CONSOLE_SEVERITY_DEBUG_BIT, col, fmt, __VA_ARGS__)

#define KCOL_TRACE(col, fmt, ...) \
  KCOL_LOG(CONSOLE_SEVERITY_TRACE_BIT, col, fmt, __VA_ARGS__)

#define KCOL_WARN(col, fmt, ...) \
  KCOL_LOG(CONSOLE_SEVERITY_WARN_BIT, col, fmt, __VA_ARGS__)

#define KCOL_ERROR(col, fmt, ...) \
  KCOL_LOG(CONSOLE_SEVERITY_ERROR_BIT, col, fmt, __VA_ARGS__)

#define KCOL_FATAL(col, fmt, ...) \
  KCOL_LOG(CONSOLE_SEVERITY_FATAL_BIT, col, fmt, __VA_ARGS__)

// Default log macros

#define KINFO(fmt, ...) KCOL_INFO(KANSI_COL_DEFAULT, fmt, __VA_ARGS__)

#define KDEBUG(fmt, ...) KCOL_DEBUG(KANSI_COL_CYAN, fmt, __VA_ARGS__)

#define KTRACE(fmt, ...) KCOL_TRACE(KANSI_COL_GREY, fmt, __VA_ARGS__)

#define KWARN(fmt, ...) KCOL_WARN(KANSI_COL_YELLOW, fmt, __VA_ARGS__)

#define KERROR(fmt, ...) KCOL_ERROR(KANSI_COL_RED, fmt, __VA_ARGS__)

#define KFATAL(fmt, ...) KCOL_FATAL(KANSI_COL_BHL_RED, fmt, __VA_ARGS__)

#include <stdarg.h>

typedef enum console_severity_bit {
  CONSOLE_SEVERITY_NONE_BIT = 0,
  CONSOLE_SEVERITY_INFO_BIT = 1 << 1,
  CONSOLE_SEVERITY_TRACE_BIT = 1 << 2,
  CONSOLE_SEVERITY_DEBUG_BIT = 1 << 3,
  CONSOLE_SEVERITY_WARN_BIT = 1 << 4,
  CONSOLE_SEVERITY_ERROR_BIT = 1 << 5,
  CONSOLE_SEVERITY_FATAL_BIT = 1 << 6,
} console_severity_bit_t;

typedef int console_filter_t;

const char* console_severity_to_string(console_severity_bit_t lv);

typedef void (*PFN_console_callback_t)(console_severity_bit_t lv,
                                       const char* file, i32_t line,
                                       const char* col, const char* fmt,
                                       va_list args);

typedef struct console {
  const char* output_file;
  console_filter_t filter;
  PFN_console_callback_t callback;
} console_t;

void console_log(console_severity_bit_t lv, const char* file, i32_t line,
                 const char* col, const char* fmt, ...);

void console_vlog(console_severity_bit_t lv, const char* file, i32_t line,
                  const char* col, const char* fmt, va_list args);

const char* ansi_col(const char indent);
const char* ansi_hl_col(const char indent);

#ifdef __cplusplus
}
#endif
#endif
