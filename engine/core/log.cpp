/**
 * @file main.cpp
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

#include "core/log.hpp"
#include <cstdio>
#include <cstdlib>

namespace kryos {

void _assert(const char* filename, int line, const char* format, ...)
{
  va_list args;
  va_start(args, format);
  _assert(filename, line, format, args);
  va_end(args);
}

void _assert(const char* filename, int line, const char* format, va_list args)
{
  constexpr size_t buffer_length = 10000;
  char message_buffer[buffer_length];
  vsnprintf(message_buffer, buffer_length, format, args);

  std::fprintf(stderr, "%s__assert__ at %s:%d:\n%s%s",
               log_context::severity::ansi_fatal, filename, line,
               message_buffer, log_context::severity::ansi_reset);
  std::abort();
}

const char* log_context::severity::to_c_str(severity::level level)
{
  switch (level) {
  case none:
    return "none";
  case info:
    return "info";
  case warn:
    return "warn";
  case error:
    return "error";
  case fatal:
    return "fatal";
  case trace:
    return "trace";
  case debug:
    return "debug";
  default:
    return "undefined";
  }
}

const char* log_context::severity::to_ansi_color(severity::level level)
{
  switch (level) {
  case none:
    return ansi_reset;
  case info:
    return ansi_info;
  case warn:
    return ansi_warn;
  case error:
    return ansi_error;
  case fatal:
    return ansi_fatal;
  case trace:
    return ansi_trace;
  case debug:
    return ansi_debug;
  default:
    return ansi_reset;
  }
}

} // namespace kryos
