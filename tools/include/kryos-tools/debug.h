/// ------------------------------------------------------------------------ ///
/// This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine) ///
/// @file debug.h                                                            ///
/// ------------------------------------------------------------------------ ///
/// @copyright (c) 2024 Oniup (https://github.com/Oniup)                     ///
///                                                                          ///
/// Licensed under the Apache License, Version 2.0 (the "License");          ///
/// you may not use this file except in compliance with the License.         ///
/// You may obtain a copy of the License at                                  ///
///                                                                          ///
///   http://www.apache.org/licenses/LICENSE-2.0                             ///
///                                                                          ///
/// Unless required by applicable law or agreed to in writing, software      ///
/// distributed under the License is distributed on an "AS IS" BASIS,        ///
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. ///
/// See the License for the specific language governing permissions and      ///
/// limitations under the License.                                           ///
/// ------------------------------------------------------------------------ ///

#ifndef KRYOS__TOOLS__DEBUG_H
#define KRYOS__TOOLS__DEBUG_H
#ifdef __cplusplus
extern "C" {
#endif

#include "kryos-tools/defines.h"
#include <stdarg.h>
#include <stdlib.h>

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
    #define TRACE(...) \
        intl_print_log_message(DEBUG_LOG_LEVEL_FLAG_TRACE, __FILE__, __LINE__, NULL, __VA_ARGS__)
    #define INFO(...) \
        intl_print_log_message(DEBUG_LOG_LEVEL_FLAG_INFO, __FILE__, __LINE__, NULL, __VA_ARGS__)
    #define DEBUG(...) \
        intl_print_log_message(DEBUG_LOG_LEVEL_FLAG_DEBUG, __FILE__, __LINE__, NULL, __VA_ARGS__)
#else
    #define TRACE(...)
    #define INFO(...)
    #define DEBUG(...)
#endif
#define WARN(...) \
    intl_print_log_message(DEBUG_LOG_LEVEL_FLAG_WARN, __FILE__, __LINE__, NULL, __VA_ARGS__)
#define ERROR(...) \
    intl_print_log_message(DEBUG_LOG_LEVEL_FLAG_ERROR, __FILE__, __LINE__, NULL, __VA_ARGS__)

#define INTERNAL_LOG_WITH_CONDITION(expr, lv, ...)                              \
    ({                                                                          \
        if (!(expr)) {                                                          \
            intl_print_log_message(lv, __FILE__, __LINE__, #expr, __VA_ARGS__); \
        }                                                                       \
    })

#ifndef KRYOS_DISABLE_INFO_LOGS
    #define TRACE_IF(expr, ...) \
        INTERNAL_LOG_WITH_CONDITION(expr, DEBUG_LOG_LEVEL_FLAG_TRACE, __VA_ARGS__)
    #define INFO_IF(expr, ...) \
        INTERNAL_LOG_WITH_CONDITION(expr, DEBUG_LOG_LEVEL_FLAG_INFO, __VA_ARGS__)
    #define DEBUG_IF(expr, ...) \
        INTERNAL_LOG_WITH_CONDITION(expr, DEBUG_LOG_LEVEL_FLAG_DEBUG, __VA_ARGS__)
#else
    #define TRACE_IF(expr, ...)
    #define INFO_IF(expr, ...)
    #define DEBUG_IF(expr, ...)
#endif
#define WARN_IF(expr, ...) INTERNAL_LOG_WITH_CONDITION(expr, DEBUG_LOG_LEVEL_FLAG_WARN, __VA_ARGS__)
#define ERROR_IF(expr, ...) \
    INTERNAL_LOG_WITH_CONDITION(expr, DEBUG_LOG_LEVEL_FLAG_ERROR, __VA_ARGS__)

#define INTERNAL_ASSERT(expr, ...)                                                        \
    ({                                                                                    \
        if (!(expr)) {                                                                    \
            intl_print_log_message(DEBUG_LOG_LEVEL_FLAG_FATAL, __FILE__, __LINE__, #expr, \
                                   __VA_ARGS__);                                          \
            abort();                                                                      \
        }                                                                                 \
    })

#define ASSERT(expr, ...) INTERNAL_ASSERT(expr, __VA_ARGS__)
#ifndef NDEBUG
    #define DEBUG_ASSERT(expr, ...) INTERNAL_ASSERT(expr, __VA_ARGS__)
#else
    #define DEBUG_DEBUG_ASSERT(expr, ...)
#endif

typedef int debug_log_level_t;
typedef enum debug_log_level_flag {
    DEBUG_LOG_LEVEL_FLAG_NONE = 0,
    DEBUG_LOG_LEVEL_FLAG_TRACE = 0X01,
    DEBUG_LOG_LEVEL_FLAG_INFO = 0X02,
    DEBUG_LOG_LEVEL_FLAG_DEBUG = 0X04,
    DEBUG_LOG_LEVEL_FLAG_WARN = 0X08,
    DEBUG_LOG_LEVEL_FLAG_ERROR = 0X10,
    DEBUG_LOG_LEVEL_FLAG_FATAL = 0X20,
} debug_log_level_flag_t;

KRYAPI const char* debug_log_level_flag_as_cstr(debug_log_level_flag_t level);

typedef enum debug_out_target {
    DEBUG_OUT_TARGET_STDOUT,
    DEBUG_OUT_TARGET_STDERR,
    DEBUG_OUT_TARGET_LOG_FILE,
} debug_out_target_t;

typedef struct global_runtime_debug_options {
    debug_log_level_t enable_level;
    struct {
        b8 expression;
        b8 file;
        b8 line;
        b8 terminal_ansi_color;
    } enable;
    struct {
        b8 enable;
        b8 terminal_ansi_color;
        const char* p_filename;
    } io;
} global_runtime_debug_options_t;

KRYAPI global_runtime_debug_options_t* get_global_runtime_debug_options();

KRYAPI void intl_print_log_message(debug_log_level_flag_t level, const char* p_filename, i32 line,
                                   const char* p_expression, const char* p_format, ...);

inline b8 failed_error(b8 condition, const char* error_message, ...) {
    if (!condition) {
        va_list args;
        va_start(args, error_message);
        ERROR(error_message, args);
        va_end(args);
        return true;
    }
    return false;
}

#ifdef __cplusplus
}
#endif
#endif
