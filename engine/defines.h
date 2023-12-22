/**
 * @file defines.h
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

#ifndef KRYOS__DEFINES_H_
#define KRYOS__DEFINES_H_
#ifdef __cplusplus
extern "C" {
#endif

#define KANSI_COL_RESET "\x1b[0m"

#define KANSI_COL_DEFAULT "\x1b[0m"
#define KANSI_COL_BLACK "\x1b[30m"
#define KANSI_COL_RED "\x1b[31m"
#define KANSI_COL_GREEN "\x1b[32m"
#define KANSI_COL_YELLOW "\x1b[33m"
#define KANSI_COL_BLUE "\x1b[34m"
#define KANSI_COL_MAGENTA "\x1b[35m"
#define KANSI_COL_CYAN "\x1b[36m"
#define KANSI_COL_WHITE "\x1b[37m"
#define KANSI_COL_GREY "\x1b[90m"

#define KANSI_COL_B_RED "\x1b[91m"
#define KANSI_COL_B_GREEN "\x1b[92m"
#define KANSI_COL_B_YELLOW "\x1b[93m"
#define KANSI_COL_B_BLUE "\x1b[94m"
#define KANSI_COL_B_MAGENTA "\x1b[95m"
#define KANSI_COL_B_CYAN "\x1b[96m"
#define KANSI_COL_B_WHITE "\x1b[97m"

#define KANSI_COL_HL_GREY "\x1b[37;100"
#define KANSI_COL_HL_RED "\x1b[37;41m"
#define KANSI_COL_HL_GREEN "\x1b[37;42m"
#define KANSI_COL_HL_YELLOW "\x1b[30;43m"
#define KANSI_COL_HL_BLUE "\x1b[37;44m"
#define KANSI_COL_HL_MAGENTA "\x1b[37;45m"
#define KANSI_COL_HL_CYAN "\x1b[437;6m"
#define KANSI_COL_HL_WHITE "\x1b[37;47m"

#define KANSI_COL_BHL_RED "\x1b[37;101m"
#define KANSI_COL_BHL_GREEN "\x1b[30;102m"
#define KANSI_COL_BHL_YELLOW "\x1b[30;103m"
#define KANSI_COL_BHL_BLUE "\x1b[37;104m"
#define KANSI_COL_BHL_MAGENTA "\x1b[30;105m"
#define KANSI_COL_BHL_CYAN "\x1b[30;106m"
#define KANSI_COL_BHL_WHITE "\x1b[30;107m"

#ifndef NDEBUG
#define KASSERT(expression, fmt, ...) \
  (void)((!!(expression)) || (KFATAL(fmt, __VA_ARGS__), 0))
#else
#define KASSERT(expression, fmt, ...)
#endif

typedef char i8_t;
typedef short i16_t;
typedef int i32_t;
typedef long int i64_t;

typedef unsigned char ui8_t;
typedef unsigned short ui16_t;
typedef unsigned int ui32_t;
typedef unsigned long int ui64_t;

#ifdef __cplusplus
typedef bool b8_t;
#else
typedef _Bool b8_t;
#define true 1
#define false 0
#endif

#ifdef __cplusplus
}
#endif
#endif
