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

void string_destroy(string_t str)
{
  if (str != NULL) {
    char* ptr = (char*)str - sizeof(string_header_t);
    free(ptr);
  }
}

string_header_t* string_header(string_t str)
{
  return (string_header_t*)((char*)str - sizeof(string_header_t));
}

size_t string_len(string_t str)
{
  return string_header(str)->len;
}

size_t string_cap(string_t str)
{
  return string_header(str)->cap;
}

string_t string_resize_cap(string_t str, size_t cap)
{
  string_header_t* meta = string_header(str);
  string_header_t* temp = realloc(meta, sizeof(string_header_t) + cap);
  KASSERT(temp,
          "Failed to copy string (%zu) into dest (%zu) due "
          "to realloc failing",
          cap, meta->cap);
  meta = temp;
  meta->cap = cap;
  return (string_t)((char*)meta + sizeof(string_header_t));
}

string_t string_create(const char* fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  char* result = string_vcreate(fmt, args);
  va_end(args);
  return result;
}

string_t string_append(string_t dest, const char* fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  dest = string_vappend(dest, fmt, args);
  va_end(args);
  return dest;
}

string_t string_copy(string_t dest, const char* fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  dest = string_vcopy(dest, fmt, args);
  va_end(args);
  return dest;
}

string_t string_vcreate(const char* fmt, va_list args)
{
  char buf[KSTR_MAX_VSPRINTF_BUF_SIZE];
  vsprintf(buf, fmt, args);
  size_t len = strlen(buf);
  size_t cap = len + 1;

  string_header_t* meta = malloc(sizeof(string_header_t) + cap);
  KASSERT(meta, "Failed to create string \"%s\" due to malloc failing", buf);

  char* str = (char*)meta + sizeof(string_header_t);
  strncpy(str, buf, len);
  str[len] = '\0';

  meta->len = len;
  meta->cap = cap;
  return (string_t)str;
}

string_t string_vcopy(string_t dest, const char* fmt, va_list args)
{
  if (dest != NULL) {
    string_header_t* meta = string_header(dest);

    char buf[KSTR_MAX_VSPRINTF_BUF_SIZE];
    vsprintf(buf, fmt, args);
    size_t buf_len = strlen(buf);

    if (buf_len >= meta->cap) {
      dest = string_resize_cap(dest, buf_len + 1);
    }
    meta->len = buf_len;

    dest = (char*)meta + sizeof(string_header_t);
    strncpy(dest, buf, buf_len);
    dest[meta->len] = '\0';

    return dest;
  }

  return string_vcreate(fmt, args);
}

string_t string_vappend(string_t dest, const char* fmt, va_list args)
{
  if (dest != NULL) {
    string_header_t* meta = string_header(dest);

    char buf[KSTR_MAX_VSPRINTF_BUF_SIZE];
    vsprintf(buf, fmt, args);

    size_t buf_len = strlen(buf);
    size_t old_len = meta->len;
    meta->len = buf_len + meta->len;

    if (meta->len >= meta->cap) {
      dest = string_resize_cap(dest, meta->len + 1);
    }

    dest = (char*)meta + sizeof(string_header_t);
    strncpy(dest + old_len, buf, buf_len);
    dest[meta->len] = '\0';
    return dest;
  }

  return string_vcreate(fmt, args);
}
