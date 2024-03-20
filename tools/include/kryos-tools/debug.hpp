/* ------------------------------------------------------------------------ *
 * This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine) *
 * @file debug.hpp                                                          *
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

#ifndef KRYOS__TOOLS__DEBUG_HPP
#define KRYOS__TOOLS__DEBUG_HPP

#include "kryos-tools/defines.hpp"
#include <cstdlib>

#define DEBUG_ANSI_PREFIX "\x1b["
#define DEBUG_ANSI_SUFIX "m"
#define DEBUG_ANSI_APPEND ";"
#define DEBUG_ANSI_RESET "\x1b[0m"

#define DEBUG_ANSI_BOLD = "1";
#define DEBUG_ANSI_ITALICIZE = "3";
#define DEBUG_ANSI_UNDERLINE = "4";

#define DEBUG_ANSI_FG_BLACK "30"
#define DEBUG_ANSI_FG_RED "31"
#define DEBUG_ANSI_FG_GREEN "32"
#define DEBUG_ANSI_FG_YELLOW "33"
#define DEBUG_ANSI_FG_BLUE "34"
#define DEBUG_ANSI_FG_MAGENTA "35"
#define DEBUG_ANSI_FG_CYAN "36"
#define DEBUG_ANSI_FG_WHITE "37"

#define DEBUG_ANSI_BG_BLACK "40"
#define DEBUG_ANSI_BG_RED "41"
#define DEBUG_ANSI_BG_GREEN "42"
#define DEBUG_ANSI_BG_YELLOW "43"
#define DEBUG_ANSI_BG_BLUE "44"
#define DEBUG_ANSI_BG_MAGENTA "45"
#define DEBUG_ANSI_BG_CYAN "46"
#define DEBUG_ANSI_BG_WHITE "47"

#define MAX_ASSERT_MSG_SIZE 2000

#ifndef KRYOS_DISABLE_INFO_LOGS
    #define TRACE(...)                                                                      \
        DebugLogger::printLogMessage(DebugLogLevel::TraceFlag, __FILE__, __LINE__, nullptr, \
                                     __VA_ARGS__)
    #define INFO(...)                                                                      \
        DebugLogger::printLogMessage(DebugLogLevel::InfoFlag, __FILE__, __LINE__, nullptr, \
                                     __VA_ARGS__)
    #define DEBUG(...)                                                                      \
        DebugLogger::printLogMessage(DebugLogLevel::DebugFlag, __FILE__, __LINE__, nullptr, \
                                     __VA_ARGS__)
#else
    #define TRACE(...)
    #define INFO(...)
    #define DEBUG(...)
#endif
#define WARN(...) \
    DebugLogger::printLogMessage(DebugLogLevel::WarnFlag, __FILE__, __LINE__, nullptr, __VA_ARGS__)
#define ERROR(...) \
    DebugLogger::printLogMessage(DebugLogLevel::ErrorFlag, __FILE__, __LINE__, nullptr, __VA_ARGS__)

#define INTERNAL_LOG_WITH_CONDITION(expr, lv, ...)                                    \
    ({                                                                                \
        if (!(expr)) {                                                                \
            DebugLogger::printLogMessage(lv, __FILE__, __LINE__, #expr, __VA_ARGS__); \
        }                                                                             \
    })

#ifndef KRYOS_DISABLE_INFO_LOGS
    #define TRACE_IF(expr, ...) \
        INTERNAL_LOG_WITH_CONDITION(expr, DebugLogLevel::TraceFlag, __VA_ARGS__)
    #define INFO_IF(expr, ...) \
        INTERNAL_LOG_WITH_CONDITION(expr, DebugLogLevel::InfoFlag, __VA_ARGS__)
    #define DEBUG_IF(expr, ...) \
        INTERNAL_LOG_WITH_CONDITION(expr, DebugLogLevel::DebugFlag, __VA_ARGS__)
#else
    #define TRACE_IF(expr, ...)
    #define INFO_IF(expr, ...)
    #define DEBUG_IF(expr, ...)
#endif
#define WARN_IF(expr, ...) INTERNAL_LOG_WITH_CONDITION(expr, DebugLogLevel::WarnFlag, __VA_ARGS__)
#define ERROR_IF(expr, ...) INTERNAL_LOG_WITH_CONDITION(expr, DebugLogLevel::ErrorFlag, __VA_ARGS__)

#define INTERNAL_ASSERT(expr, ...)                                                            \
    ({                                                                                        \
        if (!(expr)) {                                                                        \
            DebugLogger::printLogMessage(DebugLogLevel::FatalFlag, __FILE__, __LINE__, #expr, \
                                         __VA_ARGS__);                                        \
            std::abort();                                                                     \
        }                                                                                     \
    })

#define ASSERT(expr, ...) INTERNAL_ASSERT(expr, __VA_ARGS__)
#ifndef NDEBUG
    #define DEBUG_ASSERT(expr, ...) INTERNAL_ASSERT(expr, __VA_ARGS__)
#else
    #define DEBUG_DEBUG_ASSERT(expr, ...)
#endif

struct KRYOS_API DebugLogLevel {
    using Value = i32;

    enum Flag {
        NoneFlag = 0,
        TraceFlag = 0X01,
        InfoFlag = 0X02,
        DebugFlag = 0X04,
        WarnFlag = 0X08,
        ErrorFlag = 0X10,
        FatalFlag = 0X20,
    };

    static const char* asCString(DebugLogLevel::Flag level);
};

struct KRYOS_API DebugOutTarget {
    enum Type {
        StdOut,
        StdError,
        File,
    };

    static const char* asCString(DebugOutTarget::Type target);
};

// FIXME: Make debugger not a singleton
struct KRYOS_API DebugLogger {
    DebugLogLevel::Value enable_level;
    struct {
        bool expression;
        bool file;
        bool line;
        bool terminal_ansi_color;
    } enable;
    struct {
        bool enable;
        bool terminal_ansi_color;
        const char* filename;
    } io;

    static constexpr DebugLogger getDefaults();

    static DebugLogger& getInstance();
    static void printLogMessage(DebugLogLevel::Flag level, const char* filename, i32 line,
                                const char* expression, const char* format, ...);

private:
    void logMessageToTargetArgs(DebugOutTarget::Type out, DebugLogLevel::Flag level,
                                const char* filename, i32 line, const char* expression,
                                const char* format, va_list args);
    void messageBasedOnCondition(bool condition, std::FILE* out, const char* format, ...);
    void messageWithConditionalMessageArgs(bool condition, std::FILE* out, const char* format,
                                           va_list args);
    void messageFormat(std::FILE* out, DebugLogLevel::Flag level, bool ansi_color,
                       const char* filename, i32 line, const char* expression, const char* format,
                       va_list args);
    void ansiColorPrefix(bool ansi_color, std::FILE* out, DebugLogLevel::Flag level);
};

#endif
