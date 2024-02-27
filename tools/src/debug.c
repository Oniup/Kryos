/// ------------------------------------------------------------------------ ///
/// This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine) ///
/// @file debug.c                                                            ///
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

#include "kryos-tools/debug.h"
#include <stdarg.h>
#include <stdio.h>

const char* debug_log_level_flag_as_cstring(debug_log_level_flag_t level) {
    switch (level) {
        case DEBUG_LOG_LEVEL_FLAG_NONE:
            return "";
        case DEBUG_LOG_LEVEL_FLAG_TRACE:
            return "Trace";
        case DEBUG_LOG_LEVEL_FLAG_INFO:
            return "Info";
        case DEBUG_LOG_LEVEL_FLAG_DEBUG:
            return "Debug";
        case DEBUG_LOG_LEVEL_FLAG_WARN:
            return "Warning";
        case DEBUG_LOG_LEVEL_FLAG_ERROR:
            return "Error";
        case DEBUG_LOG_LEVEL_FLAG_FATAL:
            return "Fatal";
    }
}

const char* debug_out_target_as_cstring(debug_out_target_t target) {
    switch (target) {
        case DEBUG_OUT_TARGET_STDOUT:
            return "stdout";
        case DEBUG_OUT_TARGET_STDERR:
            return "stderror";
        case DEBUG_OUT_TARGET_LOG_FILE:
            return "logfile";
    };
}

global_runtime_debug_options_t* get_global_runtime_debug_options() {
    return &_kint_debug_settings;
}

void _kint_print_log_message(debug_log_level_flag_t level, const char* p_filename, i32 line,
                             const char* p_expression, const char* p_format, ...) {
    va_list args;
    va_start(args, p_format);
    _kint_log_message_to_target_args(DEBUG_OUT_TARGET_LOG_FILE, level, p_filename, line,
                                     p_expression, p_format, args);
    if (level > DEBUG_LOG_LEVEL_FLAG_WARN) {
        _kint_log_message_to_target_args(DEBUG_OUT_TARGET_STDERR, level, p_filename, line,
                                         p_expression, p_format, args);
    } else {
        _kint_log_message_to_target_args(DEBUG_OUT_TARGET_STDOUT, level, p_filename, line,
                                         p_expression, p_format, args);
    }
    va_end(args);
}

void _kint_log_message_to_target_args(debug_out_target_t out, debug_log_level_flag_t level,
                                      const char* p_filename, i32 line, const char* p_expression,
                                      const char* p_format, va_list args) {
    switch (out) {
        case DEBUG_OUT_TARGET_STDOUT:
            _kint_message_format(stdout, level, _kint_debug_settings.enable.terminal_ansi_color,
                                 p_filename, line, p_expression, p_format, args);
            break;
        case DEBUG_OUT_TARGET_STDERR:
            _kint_message_format(stderr, level, _kint_debug_settings.enable.terminal_ansi_color,
                                 p_filename, line, p_expression, p_format, args);
            break;
        case DEBUG_OUT_TARGET_LOG_FILE:
            {
                FILE* p_stream = NULL;
                errno_t err = 0;
                err = fopen_s(&p_stream, _kint_debug_settings.io.p_filename, "a");
                if (err != 0) {
                    fprintf(stderr, "Failed to open \"%s\" with error number = %d",
                            _kint_debug_settings.io.p_filename, err);
                    _kint_debug_settings.io.enable = false;
                } else {
                    _kint_message_format(p_stream, level,
                                         _kint_debug_settings.io.terminal_ansi_color, p_filename,
                                         line, p_expression, p_format, args);
                    fclose(p_stream);
                }
            }
            break;
    }
}

void _kint_message_format(FILE* p_out, debug_log_level_flag_t level, b8 ansi_color,
                          const char* p_filename, i32 line, const char* p_expression,
                          const char* p_format, va_list args) {
    _kint_ansi_color_prefix(ansi_color, p_out, level);
    fprintf(p_out, "%s ", debug_log_level_flag_as_cstring(level));
    _kint_message_based_on_condition(_kint_debug_settings.enable.file && p_filename != NULL, p_out,
                                     "File: %s, ", p_filename);
    _kint_message_based_on_condition(_kint_debug_settings.enable.line && line != -1, p_out,
                                     "Line: %d, ", line);
    _kint_message_based_on_condition(_kint_debug_settings.enable.expression && p_expression != NULL,
                                     p_out, "expr: %s, ", p_expression);
    if (p_format != NULL) {
        fprintf(p_out, "Msg: ");
        vfprintf(p_out, p_format, args);
    }
    _kint_message_based_on_condition(ansi_color, p_out, "%s", DEBUG_ANSI_RESET);
    fprintf(p_out, "\n");
    fflush(p_out);
}

void _kint_ansi_color_prefix(b8 ansi_color, FILE* p_out, debug_log_level_flag_t level) {
    if (ansi_color) {
        switch (level) {
            case DEBUG_LOG_LEVEL_FLAG_NONE:
                break;
            case DEBUG_LOG_LEVEL_FLAG_TRACE:
                fprintf(p_out, "%s%sm", DEBUG_ANSI_PREFIX, DEBUG_ANSI_FG_BLUE);
                break;
            case DEBUG_LOG_LEVEL_FLAG_INFO:
                fprintf(p_out, "%s%sm", DEBUG_ANSI_PREFIX, DEBUG_ANSI_FG_GREEN);
                break;
            case DEBUG_LOG_LEVEL_FLAG_DEBUG:
                fprintf(p_out, "%s%sm", DEBUG_ANSI_PREFIX, DEBUG_ANSI_FG_MAGENTA);
                break;
            case DEBUG_LOG_LEVEL_FLAG_WARN:
                fprintf(p_out, "%s%sm", DEBUG_ANSI_PREFIX, DEBUG_ANSI_FG_YELLOW);
                break;
            case DEBUG_LOG_LEVEL_FLAG_ERROR:
                fprintf(p_out, "%s%sm", DEBUG_ANSI_PREFIX, DEBUG_ANSI_FG_RED);
                break;
            case DEBUG_LOG_LEVEL_FLAG_FATAL:
                fprintf(p_out, "%s%s;%sm", DEBUG_ANSI_PREFIX, DEBUG_ANSI_FG_BLACK,
                        DEBUG_ANSI_BG_RED);
                break;
        }
    }
}

void _kint_message_based_on_condition(b8 condition, FILE* p_out, const char* p_format, ...) {
    if (condition) {
        va_list args;
        va_start(args, p_format);
        vfprintf(p_out, p_format, args);
        va_end(args);
    }
}

void _kint_message_with_conditional_message_args(b8 condition, FILE* p_out, const char* p_format,
                                                 va_list args) {
    if (condition) {
        vfprintf(p_out, p_format, args);
    }
}
