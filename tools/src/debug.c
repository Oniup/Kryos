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

static global_runtime_debug_options_t g_db_opts = {
    // Doesn't include trace and info flags by default
    .lv_filter = DEBUG_LOG_LEVEL_FLAG_DEBUG | DEBUG_LOG_LEVEL_FLAG_WARN |
                 DEBUG_LOG_LEVEL_FLAG_ERROR | DEBUG_LOG_LEVEL_FLAG_FATAL,
    .enable =
        {
            .expr = true,
            .file = true,
            .line = true,
            .ansi_col = true,
        },
    .io =
        {
            .enable = true,
            .ansi_col = false,
            .p_fpath = "kryos-engine.log",
        },
};

void print_log_msg_to_target_v(debug_out_target_t out, debug_log_level_flag_t lv,
                               const char* p_fpath, i32 line, const char* p_expr,
                               const char* p_fmt, va_list args);
void print_msg_with_conditional(b8 condition, FILE* p_out, const char* p_fmt, ...);
void print_msg_with_conditional_msg_v(b8 condition, FILE* p_out, const char* p_fmt,
                                      va_list args);
void print_msg_fmt(FILE* p_out, debug_log_level_flag_t lv, b8 ansi_col,
                   const char* p_fpath, i32 line, const char* p_expr, const char* p_fmt,
                   va_list args);
void print_ansi_col_prefix(b8 ansi_col, FILE* p_out, debug_log_level_flag_t lv);

const char* debug_log_level_flag_as_cstr(debug_log_level_flag_t lv) {
    switch (lv) {
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

global_runtime_debug_options_t* get_global_runtime_debug_options() {
    return &g_db_opts;
}

void intl_print_log_msg(debug_log_level_flag_t lv, const char* p_fpath, i32 line,
                        const char* p_expr, const char* p_fmt, ...) {
    va_list args;
    va_start(args, p_fmt);
    print_log_msg_to_target_v(DEBUG_OUT_TARGET_LOG_FILE, lv, p_fpath, line, p_expr, p_fmt,
                              args);
    if (lv > DEBUG_LOG_LEVEL_FLAG_WARN) {
        print_log_msg_to_target_v(DEBUG_OUT_TARGET_STDERR, lv, p_fpath, line, p_expr,
                                  p_fmt, args);
    } else {
        print_log_msg_to_target_v(DEBUG_OUT_TARGET_STDOUT, lv, p_fpath, line, p_expr,
                                  p_fmt, args);
    }
    va_end(args);
}

void print_log_msg_to_target_v(debug_out_target_t out, debug_log_level_flag_t lv,
                               const char* p_fpath, i32 line, const char* p_expr,
                               const char* p_fmt, va_list args) {
    switch (out) {
        case DEBUG_OUT_TARGET_STDOUT:
            print_msg_fmt(stdout, lv, g_db_opts.enable.ansi_col, p_fpath, line, p_expr,
                          p_fmt, args);
            break;
        case DEBUG_OUT_TARGET_STDERR:
            print_msg_fmt(stderr, lv, g_db_opts.enable.ansi_col, p_fpath, line, p_expr,
                          p_fmt, args);
            break;
        case DEBUG_OUT_TARGET_LOG_FILE:
            {
                FILE* p_stream = NULL;
                errno_t err = 0;
                err = fopen_s(&p_stream, g_db_opts.io.p_fpath, "a");
                if (err != 0) {
                    fprintf(stderr, "Failed to open \"%s\" with error number = %d",
                            g_db_opts.io.p_fpath, err);
                    g_db_opts.io.enable = false;
                } else {
                    print_msg_fmt(p_stream, lv, g_db_opts.io.ansi_col, p_fpath, line,
                                  p_expr, p_fmt, args);
                    fclose(p_stream);
                }
            }
            break;
    }
}

void print_msg_fmt(FILE* p_out, debug_log_level_flag_t lv, b8 ansi_col,
                   const char* p_fpath, i32 line, const char* p_expr, const char* p_fmt,
                   va_list args) {
    print_ansi_col_prefix(ansi_col, p_out, lv);
    fprintf(p_out, "%s ", debug_log_level_flag_as_cstr(lv));
    print_msg_with_conditional(g_db_opts.enable.file && p_fpath != NULL, p_out,
                               "File: %s, ", p_fpath);
    print_msg_with_conditional(g_db_opts.enable.line && line != -1, p_out, "Line: %d, ",
                               line);
    print_msg_with_conditional(g_db_opts.enable.expr && p_expr != NULL, p_out,
                               "expr: %s, ", p_expr);
    if (p_fmt != NULL) {
        fprintf(p_out, "Msg: ");
        vfprintf(p_out, p_fmt, args);
    }
    print_msg_with_conditional(ansi_col, p_out, "%s", DEBUG_ANSI_RESET);
    fprintf(p_out, "\n");
}

void print_ansi_col_prefix(b8 ansi_col, FILE* p_out, debug_log_level_flag_t lv) {
    if (ansi_col) {
        switch (lv) {
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

void print_msg_with_conditional(b8 condition, FILE* p_out, const char* p_fmt, ...) {
    if (condition) {
        va_list args;
        va_start(args, p_fmt);
        vfprintf(p_out, p_fmt, args);
        va_end(args);
    }
}

void print_msg_with_conditional_msg_v(b8 condition, FILE* p_out, const char* p_fmt,
                                      va_list args) {
    if (condition) {
        vfprintf(p_out, p_fmt, args);
    }
}
