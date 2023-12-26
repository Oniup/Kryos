/**
 * @file logging.cpp
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

#ifndef KDISABLE_LOGGING

 #include "core/logging.hpp"
 #include "core/time.hpp"

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

namespace kryos {

const char* console_severity_to_string(LogSeverityBit lv)
{
  switch (lv) {
  case LogSeverity_InfoBit:
    return "Info";
  case LogSeverity_DebugBit:
    return "Debug";
  case LogSeverity_TraceBit:
    return "Trace";
  case LogSeverity_WarnBit:
    return "Warning";
  case LogSeverity_ErrorBit:
    return "Error";
  case LogSeverity_FatalBit:
    return "Fatal";
  case LogSeverity_NoneBit:
    return "None";
  };
  return "Undefined";
}

void console_log(LogSeverityBit lv, const char* file, i32_t line,
                 const char* col, const char* fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  console_vlog(lv, file, line, col, fmt, args);
  va_end(args);
}

void console_vlog(LogSeverityBit lv, const char* file, i32_t line,
                  const char* col, const char* fmt, va_list args)
{
  const char* pfx_fmt = nullptr;
  if (lv == LogSeverity_FatalBit) {
    pfx_fmt = "%s%s %s %s:%d: ";
  }
  else {
    pfx_fmt = "%s%s %s: ";
  }

  const ui64_t pfx_fmt_len = strlen(pfx_fmt);
  const ui64_t fmt_len = strlen(fmt);

  constexpr ui64_t time_buf_size = 64;
  char* time_buf = (char*)malloc(time_buf_size);
  get_time_as_c_str(time_buf, time_buf_size);
  const char* str_lv = console_severity_to_string(lv);

  // Printing to console
  if (lv == LogSeverity_FatalBit) {
    printf(pfx_fmt, col, time_buf, str_lv, file, line);
  }
  else {
    printf(pfx_fmt, col, time_buf, str_lv);
  }
  vprintf(fmt, args);
  printf("%s\n", KANSI_COL_RESET);
  fflush(stdout); // Some IDE's require this like CLion

 #ifndef KDISABLE_LOGGING_OUTPUT_FILE
  pfx_fmt = "%s%s %s %s:%d: ";
  FILE* stream = fopen("kryos.log", "a");
  fprintf(stream, pfx_fmt, "", time_buf, str_lv, file, line);
  vfprintf(stream, fmt, args);
  fprintf(stream, "\n");
  fclose(stream);
 #endif
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

} // namespace kryos

#endif
