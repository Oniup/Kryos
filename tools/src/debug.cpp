/* ------------------------------------------------------------------------ *
 * This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine) *
 * @file debug.cpp                                                          *
 * ------------------------------------------------------------------------ *
 * @copyright (c) 2024 Oniup (https://github.com/Oniup)                     *
 *                                                                          *
 * Licensed under the Apache License, Version 2.0 (the "License");          *
 * you may not use this file except in compliance with the License.         *
 * You may obtain a copy of the License at                                  *
 *                                                                          *
 *   http://www.apache.org/licenses/LICENSE-2.0                             *
 *                                                                          *
 * Unless required by applicable law or agreed to in writing, software      *
 * distributed under the License is distributed on an "AS IS" BASIS,        *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. *
 * See the License for the specific language governing permissions and      *
 * limitations under the License.                                           *
 * ------------------------------------------------------------------------ */

#include "kryos-tools/debug.hpp"
#include <cstdarg>
#include <cstdio>

const char* DebugLogLevel::asCString(DebugLogLevel::Flag level) {
    switch (level) {
        case DebugLogLevel::NoneFlag:
            return "";
        case DebugLogLevel::TraceFlag:
            return "Trace";
        case DebugLogLevel::InfoFlag:
            return "Info";
        case DebugLogLevel::DebugFlag:
            return "Debug";
        case DebugLogLevel::WarnFlag:
            return "Warning";
        case DebugLogLevel::ErrorFlag:
            return "Error";
        case DebugLogLevel::FatalFlag:
            return "Fatal";
    }
}

const char* DebugOutTarget::asCString(DebugOutTarget::Type target) {
    switch (target) {
        case DebugOutTarget::StdOut:
            return "stdout";
        case DebugOutTarget::StdError:
            return "stderror";
        case DebugOutTarget::File:
            return "logfile";
    };
}

constexpr DebugLogger DebugLogger::getDefaults() {
    return {
        .enable_level = DebugLogLevel::DebugFlag | DebugLogLevel::WarnFlag |
                        DebugLogLevel::ErrorFlag | DebugLogLevel::FatalFlag,
        .enable =
            {
                .expression = true,
                .file = true,
                .line = true,
                .terminal_ansi_color = true,
            },
        .io =
            {
                .enable = true,
                .terminal_ansi_color = false,
                .filename = "kryos-engine.log",
            },
    };
}

DebugLogger& DebugLogger::getInstance() {
    static DebugLogger settings = getDefaults();
    return settings;
}

void DebugLogger::printLogMessage(DebugLogLevel::Flag level, const char* filename, i32 line,
                                  const char* expression, const char* format, ...) {
    va_list args;
    va_start(args, format);
    getInstance().implPrintLogMessage(level, filename, line, expression, format, args);
    va_end(args);
}

void DebugLogger::implPrintLogMessage(DebugLogLevel::Flag level, const char* filename, i32 line,
                                      const char* expression, const char* format, ...) {
    va_list args;
    va_start(args, format);
    logMessageToTargetArgs(DebugOutTarget::File, level, filename, line, expression, format, args);
    if (level > DebugLogLevel::WarnFlag) {
        va_start(args, format);
        logMessageToTargetArgs(DebugOutTarget::StdError, level, filename, line, expression, format,
                               args);
        va_end(args);
    } else {
        va_start(args, format);
        logMessageToTargetArgs(DebugOutTarget::StdOut, level, filename, line, expression, format,
                               args);
        va_end(args);
    }
}

void DebugLogger::logMessageToTargetArgs(DebugOutTarget::Type out, DebugLogLevel::Flag level,
                                         const char* filename, i32 line, const char* expression,
                                         const char* format, va_list args) {
    switch (out) {
        case DebugOutTarget::StdOut:
            messageFormat(stdout, level, enable.terminal_ansi_color, filename, line, expression,
                          format, args);
            break;
        case DebugOutTarget::StdError:
            messageFormat(stderr, level, enable.terminal_ansi_color, filename, line, expression,
                          format, args);
            break;
        case DebugOutTarget::File:
            {
                FILE* stream = fopen(io.filename, "a");
                if (stream != nullptr) {
                    messageFormat(stream, level, io.terminal_ansi_color, filename, line, expression,
                                  format, args);
                    fclose(stream);
                } else {
                    fprintf(stderr, "Failed to open debug log file with path \"%s\"", io.filename);
                    fflush(stderr);
                    io.enable = false;
                }
            }
            break;
    }
}

void DebugLogger::messageFormat(FILE* out, DebugLogLevel::Flag level, bool ansi_color,
                                const char* filename, i32 line, const char* expression,
                                const char* format, va_list args) {
    ansiColorPrefix(ansi_color, out, level);
    fprintf(out, "%s ", DebugLogLevel::asCString(level));
    messageBasedOnCondition(enable.file && filename != nullptr, out, "File: %s, ", filename);
    messageBasedOnCondition(enable.line && line != -1, out, "Line: %d, ", line);
    messageBasedOnCondition(enable.expression && expression != nullptr, out, "expr: %s, ", expression);
    if (format != nullptr) {
        fprintf(out, "Msg: ");
        vfprintf(out, format, args);
    }
    messageBasedOnCondition(ansi_color, out, "%s", DEBUG_ANSI_RESET);
    fprintf(out, "\n");
    fflush(out);
}

void DebugLogger::ansiColorPrefix(bool ansi_color, FILE* out, DebugLogLevel::Flag level) {
    if (ansi_color) {
        switch (level) {
            case DebugLogLevel::NoneFlag:
                break;
            case DebugLogLevel::TraceFlag:
                fprintf(out, "%s%sm", DEBUG_ANSI_PREFIX, DEBUG_ANSI_FG_BLUE);
                break;
            case DebugLogLevel::InfoFlag:
                fprintf(out, "%s%sm", DEBUG_ANSI_PREFIX, DEBUG_ANSI_FG_GREEN);
                break;
            case DebugLogLevel::DebugFlag:
                fprintf(out, "%s%sm", DEBUG_ANSI_PREFIX, DEBUG_ANSI_FG_MAGENTA);
                break;
            case DebugLogLevel::WarnFlag:
                fprintf(out, "%s%sm", DEBUG_ANSI_PREFIX, DEBUG_ANSI_FG_YELLOW);
                break;
            case DebugLogLevel::ErrorFlag:
                fprintf(out, "%s%sm", DEBUG_ANSI_PREFIX, DEBUG_ANSI_FG_RED);
                break;
            case DebugLogLevel::FatalFlag:
                fprintf(out, "%s%s;%sm", DEBUG_ANSI_PREFIX, DEBUG_ANSI_FG_BLACK, DEBUG_ANSI_BG_RED);
                break;
        }
    }
}

void DebugLogger::messageBasedOnCondition(bool condition, FILE* out, const char* format, ...) {
    if (condition) {
        va_list args;
        va_start(args, format);
        vfprintf(out, format, args);
        va_end(args);
    }
}

void DebugLogger::messageWithConditionalMessageArgs(bool condition, FILE* out, const char* format,
                                                    va_list args) {
    if (condition) {
        vfprintf(out, format, args);
    }
}
