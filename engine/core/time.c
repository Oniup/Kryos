/**
 * @file time.c
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

#include "core/time.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void get_time_as_str(char* dest, size_t size)
{
  const char* fmt = "%d:%d:%d %d:%d:%d";
  const size_t fmt_len = strlen(fmt);

  time_t t = time(NULL);
  struct tm* tinfo = localtime(&t);

  /// TODO: Check if "time_info->tm_mon + 1" still needs the +1
  snprintf(dest, size, fmt, tinfo->tm_mday, tinfo->tm_mon + 1,
           tinfo->tm_year + 1900, tinfo->tm_hour, tinfo->tm_min, tinfo->tm_sec);
}
