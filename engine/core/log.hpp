/**
 * @file log.hpp
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

#ifndef KRYOS__CORE__LOG_HPP
#define KRYOS__CORE__LOG_HPP

#include <cstdarg>

#ifndef NDEBUG
 #define KASSERT(expression, format, ...)                      \
   ({                                                          \
    if (!(expression)) {                                       \
      kryos::_assert(__FILE__, __LINE__, format, __VA_ARGS__); \
    }                                                          \
   })

#else
 #define KASSERT(condition, format, ...)
#endif

namespace kryos {

#ifndef NDEBUG
void _assert(const char* filename, int line, const char* message, ...);
void _assert(const char* filename, int line, const char* message, va_list args);
#endif

class log_context {
public:
  struct severity {
    static constexpr const char* ansi_reset = "\x1b[0m";
    static constexpr const char* ansi_info = "\x1b[0m";
    static constexpr const char* ansi_warn = "\x1b[33m";
    static constexpr const char* ansi_error = "\x1b[31m";
    static constexpr const char* ansi_fatal = "\x1b[37;101m";
    static constexpr const char* ansi_trace = "\x1b[90m";
    static constexpr const char* ansi_debug = "\x1b[36m";

    using filter = int;

    enum level {
      none = 0,
      info = 0x001,
      warn = 0x002,
      error = 0x004,
      fatal = 0x008,
      trace = 0x010,
      debug = 0x020,
    };

    const char* to_c_str(severity::level level);
    const char* to_ansi_color(severity::level level);
  };

public:
  log_context(severity::filter filter, const char* output_file,
              bool output_ansi_color = true, bool output_filename = true,
              bool output_line_number = true);

  // void log(severity::level level, const char* format, ...);
  // void vlog(severity::level level, const char* format, va_list args);

private:
  severity::filter _filter = severity::none;
  const char* _output_file = nullptr;
  bool _output_ansi_color = true;
  bool _output_filename = true;
  bool _output_line_number = true;
};

} // namespace kryos

#endif
