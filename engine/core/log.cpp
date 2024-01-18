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
#include <stdio.h>
#include <stdlib.h>

namespace kryos {

void impl_assert(const char* file, int line, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    impl_assert(file, line, fmt, args);
}

void impl_assert(const char* file, int line, const char* fmt, va_list args) {
    constexpr size_t buf_len = 10000;
    char msg_buf[buf_len];
    vsnprintf(msg_buf, buf_len, fmt, args);

    fprintf(stderr, "%sFatal at %s:%d:\n%s%s", Logger::Severity::ansi_fatal, file, line, msg_buf,
            Logger::Severity::ansi_reset);
    va_end(args);
    abort();
}

const char* Logger::Severity::to_cstr(Severity::Level lv) {
    switch (lv) {
    case none:
        return "None";
    case info:
        return "Info";
    case warn:
        return "Warn";
    case error:
        return "Error";
    case fatal:
        return "Fatal";
    case trace:
        return "Trace";
    case debug:
        return "Debug";
    default:
        return "Undefined";
    }
}

const char* Logger::Severity::to_ansi_col(Severity::Level lv) {
    switch (lv) {
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

Logger::Logger(Severity::Filter filter, const char* file, bool enable_ansi_col, bool enable_file,
               bool enable_line) {
}

} // namespace kryos
