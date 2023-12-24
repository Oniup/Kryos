/**
 * @file string.c
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

#include "containers/string.h"
#include "core/console.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* string_create(const char* fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  char* result = string_vcreate(fmt, args);
  va_end(args);
  return result;
}

char* string_append(char* dest, const char* fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  dest = string_vappend(dest, fmt, args);
  va_end(args);
  return dest;
}

char* string_copy(char* dest, const char* fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  dest = string_vcopy(dest, fmt, args);
  va_end(args);
  return dest;
}

char* string_vcreate(const char* fmt, va_list args)
{
  char buf[KSTR_MAX_VSPRINTF_BUF_SIZE];
  vsprintf(buf, fmt, args);
  ui64_t len = strlen(buf);

  char* str = malloc(len + 1);
  KASSERT(str, "Failed to create string \"%s\" due to malloc failing", buf);
  strncpy(str, buf, len);
  str[len] = '\0';
  return str;
}

char* string_vcopy(char* dest, const char* fmt, va_list args)
{
  if (dest != NULL) {
    char buf[KSTR_MAX_VSPRINTF_BUF_SIZE];
    vsprintf(buf, fmt, args);
    ui64_t len = strlen(buf);

    free(dest);
    dest = malloc(sizeof(char) * len + 1);
    KASSERT(dest, "Failed to copy string \"%s\" due to malloc failing", buf);
    strncpy(dest, buf, len);
    dest[len] = '\0';
    return dest;
  }
  return string_vcreate(fmt, args);
}

char* string_vappend(char* dest, const char* fmt, va_list args)
{
  if (dest != NULL) {
    char buf[KSTR_MAX_VSPRINTF_BUF_SIZE];
    vsprintf(buf, fmt, args);

    ui64_t buf_len = strlen(buf);
    ui64_t old_len = strlen(dest);
    ui64_t len = buf_len + old_len;

    char* temp = realloc(dest, sizeof(char) * len + 1);
    KASSERT(temp,
            "Failed to append string \"%s\" to \"%s\" due to realloc failing",
            buf, dest);
    dest = temp;

    strncpy(dest + old_len, buf, buf_len);
    dest[len] = '\0';
    return dest;
  }
  return string_vcreate(fmt, args);
}
