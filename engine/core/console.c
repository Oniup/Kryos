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
#include "core/time.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* console_severity_to_string(console_severity_bit_t lv)
{
  switch (lv) {
  case CONSOLE_SEVERITY_INFO_BIT:
    return "Info";
  case CONSOLE_SEVERITY_DEBUG_BIT:
    return "Debug";
  case CONSOLE_SEVERITY_TRACE_BIT:
    return "Trace";
  case CONSOLE_SEVERITY_WARN_BIT:
    return "Warning";
  case CONSOLE_SEVERITY_ERROR_BIT:
    return "Error";
  case CONSOLE_SEVERITY_FATAL_BIT:
    return "Fatal";
  case CONSOLE_SEVERITY_NONE_BIT:
    return "None";
  };
  return "Undefined";
}

void console_log(console_severity_bit_t lv, const char* file, i32_t line,
                 const char* col, const char* fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  console_vlog(lv, file, line, col, fmt, args);
  va_end(args);
}

void console_vlog(console_severity_bit_t lv, const char* file, i32_t line,
                  const char* col, const char* fmt, va_list args)
{
  console_t* console = &context_ptr()->console;

  const char* pfx_fmt = NULL;
  if (lv == CONSOLE_SEVERITY_FATAL_BIT) {
    pfx_fmt = "%s%s %s %s:%d: ";
  } else {
    pfx_fmt = "%s%s %s: ";
  }
  const size_t pfx_fmt_len = strlen(pfx_fmt);
  const size_t fmt_len = strlen(fmt);

  char* time_buf = (char*)malloc(KTIME_STR_MIN_BUF_SIZE);
  get_time_as_str(time_buf, KTIME_STR_MIN_BUF_SIZE);
  const char* str_lv = console_severity_to_string(lv);

  // Printing to console
  if (lv == CONSOLE_SEVERITY_FATAL_BIT) {
    printf(pfx_fmt, col, time_buf, str_lv, file, line);
  } else {
    printf(pfx_fmt, col, time_buf, str_lv);
  }
  vprintf(fmt, args);
  printf("%s\n", KANSI_COL_RESET);
  fflush(stdout); // Some IDE's require this like CLion

  if (console->output_file != NULL) {
    // Should always use this format when logging to file
    pfx_fmt = "%s%s %s %s:%d: ";
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

  if (lv == CONSOLE_SEVERITY_FATAL_BIT) {
    abort();
  }
}

const char* ansi_col(const char indent)
{
  switch (indent) {
  case 'r':
    return KANSI_COL_RED;
  case 'g':
    return KANSI_COL_GREEN;
  case 'y':
    return KANSI_COL_YELLOW;
  case 'b':
    return KANSI_COL_BLUE;
  case 'm':
    return KANSI_COL_MAGENTA;
  case 'c':
    return KANSI_COL_CYAN;
  case 'w':
    return KANSI_COL_WHITE;
  case 'e':
    return KANSI_COL_GREY;
  case 'R':
    return KANSI_COL_B_RED;
  case 'G':
    return KANSI_COL_B_GREEN;
  case 'Y':
    return KANSI_COL_B_YELLOW;
  case 'B':
    return KANSI_COL_B_BLUE;
  case 'M':
    return KANSI_COL_B_MAGENTA;
  case 'C':
    return KANSI_COL_B_CYAN;
  case 'W':
    return KANSI_COL_B_WHITE;
  default:
    return KANSI_COL_DEFAULT;
  }
}

const char* ansi_hl_col(const char indent)
{
  switch (indent) {
  case 'r':
    return KANSI_COL_HL_RED;
  case 'g':
    return KANSI_COL_HL_GREEN;
  case 'y':
    return KANSI_COL_HL_YELLOW;
  case 'b':
    return KANSI_COL_HL_BLUE;
  case 'm':
    return KANSI_COL_HL_MAGENTA;
  case 'c':
    return KANSI_COL_HL_CYAN;
  case 'w':
    return KANSI_COL_HL_WHITE;
  case 'e':
    return KANSI_COL_HL_GREY;
  case 'R':
    return KANSI_COL_BHL_RED;
  case 'G':
    return KANSI_COL_BHL_GREEN;
  case 'Y':
    return KANSI_COL_BHL_YELLOW;
  case 'B':
    return KANSI_COL_BHL_BLUE;
  case 'M':
    return KANSI_COL_BHL_MAGENTA;
  case 'C':
    return KANSI_COL_BHL_CYAN;
  case 'W':
    return KANSI_COL_BHL_WHITE;
  default:
    return KANSI_COL_DEFAULT;
  }
}
