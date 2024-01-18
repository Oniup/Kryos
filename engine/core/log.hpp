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

#include <stdarg.h>

#ifndef NDEBUG
  #define KASSERT(expr, fmt, ...)                                     \
      ({                                                              \
        if (!(expr)) {                                                \
            kryos::impl_assert(__FILE__, __LINE__, fmt, __VA_ARGS__); \
        }                                                             \
      })
#else
  #define KASSERT(condition, format, ...)
#endif

namespace kryos {

void impl_assert(const char* file, int line, const char* fmt, ...);
void impl_assert(const char* file, int line, const char* fmt, va_list args);

class Logger {
public:
    struct Severity {
        static constexpr const char* ansi_reset {"\x1b[0m"};
        static constexpr const char* ansi_info {"\x1b[0m"};
        static constexpr const char* ansi_warn {"\x1b[33m"};
        static constexpr const char* ansi_error {"\x1b[31m"};
        static constexpr const char* ansi_fatal {"\x1b[37;101m"};
        static constexpr const char* ansi_trace {"\x1b[90m"};
        static constexpr const char* ansi_debug {"\x1b[36m"};

        using Filter = int;

        enum Level {
            none = 0,
            info = 0x001,
            warn = 0x002,
            error = 0x004,
            fatal = 0x008,
            trace = 0x010,
            debug = 0x020,
        };

        const char* to_cstr(Severity::Level lv);
        const char* to_ansi_col(Severity::Level lv);
    };

public:
    Logger(Severity::Filter filter, const char* file, bool enable_ansi_col = true,
           bool enable_file = true, bool enable_line = true);

private:
    Severity::Filter m_filter {Severity::none};
    const char* m_file {nullptr};
    bool m_enable_ansi_col {true};
    bool m_enable_file {true};
    bool m_enable_line {true};
};

} // namespace kryos

#endif
