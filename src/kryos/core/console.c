/**
 * @file console.c
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

#include "core/console.h"
#include "core/context.h"
#include "utils/time.h"

#include <string.h>

const char* kry_console_severity_to_string(kry_console_severity_bit_t lv) {
  switch (lv) {
  case KRY_CONSOLE_SEVERITY_INFO_BIT:
    return "Info";
  case KRY_CONSOLE_SEVERITY_DEBUG_BIT:
    return "Debug";
  case KRY_CONSOLE_SEVERITY_TRACE_BIT:
    return "Trace";
  case KRY_CONSOLE_SEVERITY_WARN_BIT:
    return "Warning";
  case KRY_CONSOLE_SEVERITY_ERROR_BIT:
    return "Error";
  case KRY_CONSOLE_SEVERITY_FATAL_BIT:
    return "Fatal";
  case KRY_CONSOLE_SEVERITY_NONE_BIT:
    return "None";
  };
  return "Undefined";
}

void kry_console_log(kry_console_severity_bit_t lv, const char* file, int line,
                     const char* col, const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  kry_console_log_v(lv, file, line, col, fmt, args);
  va_end(args);
}

void kry_console_log_v(kry_console_severity_bit_t lv, const char* file,
                       int line, const char* col, const char* fmt,
                       va_list args) {
  kry_console_t* console = &kry_get_context()->console;

  const char* pfx_fmt = "%s%s %s %s:%d: ";
  const size_t pfx_fmt_len = strlen(pfx_fmt);
  const size_t fmt_len = strlen(fmt);

  char* time_buf = (char*)malloc(KRY_TIME_STR_MIN_BUF_SIZE);
  kry_get_time_as_str(time_buf, KRY_TIME_STR_MIN_BUF_SIZE);
  const char* str_lv = kry_console_severity_to_string(lv);

  // Printing to console
  printf(pfx_fmt, col, time_buf, str_lv, file, line);
  vprintf(fmt, args);
  printf("%s\n", KRY_ANSI_COL_RESET);
  fflush(stdout); // Some IDE's require this like CLion

  if (console->output_file != NULL) {
    FILE* file = fopen(console->output_file, "a");
    fprintf(file, pfx_fmt, "", time_buf, str_lv, file, line);
    vfprintf(file, fmt, args);
    fprintf(file, "\n");
    fclose(file);
  }

  if (console->callback != NULL) {
    console->callback(lv, file, line, col, fmt, args);
  }

  free(time_buf);

  if (lv == KRY_CONSOLE_SEVERITY_FATAL_BIT) {
    abort();
  }
}
