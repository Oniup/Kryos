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

#include "utils/string.h"
#include "core/console.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void kry_string_destroy(kry_string_t str)
{
  if (str != NULL) {
    char* ptr = (char*)str - sizeof(kry_string_meta_t);
    free(ptr);
  }
}

kry_string_meta_t* kry_string_meta(kry_string_t str)
{
  return (kry_string_meta_t*)((char*)str - sizeof(kry_string_meta_t));
}

size_t kry_string_len(kry_string_t str)
{
  return kry_string_meta(str)->len;
}

size_t kry_string_capacity(kry_string_t str)
{
  return kry_string_meta(str)->cap;
}

kry_string_t kry_string_resize_cap(kry_string_t str, size_t cap)
{
  kry_string_meta_t* meta = kry_string_meta(str);
  kry_string_meta_t* temp = realloc(meta, sizeof(kry_string_meta_t) + cap);
  KRY_ASSERT(temp,
             "Failed to copy string (%zu) into dest (%zu) due "
             "to realloc failing",
             cap, meta->cap);
  meta = temp;
  meta->cap = cap;
  return (kry_string_t)((char*)meta + sizeof(kry_string_meta_t));
}

kry_string_t kry_string_create(const char* fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  char* result = kry_string_vcreate(fmt, args);
  va_end(args);
  return result;
}

kry_string_t kry_string_append(kry_string_t dest, const char* fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  dest = kry_string_vappend(dest, fmt, args);
  va_end(args);
  return dest;
}

kry_string_t kry_string_copy(kry_string_t dest, const char* fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  dest = kry_string_vcopy(dest, fmt, args);
  va_end(args);
  return dest;
}

kry_string_t kry_string_vcreate(const char* fmt, va_list args)
{
  char buf[KRY_STR_MAX_VSPRINTF_BUF_SIZE];
  vsprintf(buf, fmt, args);
  size_t len = strlen(buf);
  size_t cap = len + 1;

  kry_string_meta_t* meta = malloc(sizeof(kry_string_meta_t) + cap);
  KRY_ASSERT(meta, "Failed to create string \"%s\" due to malloc failing", buf);

  char* str = (char*)meta + sizeof(kry_string_meta_t);
  strncpy(str, buf, len);
  str[len] = '\0';

  meta->len = len;
  meta->cap = cap;
  return (kry_string_t)str;
}

kry_string_t kry_string_vcopy(kry_string_t dest, const char* fmt, va_list args)
{
  if (dest != NULL) {
    kry_string_meta_t* meta = kry_string_meta(dest);

    char buf[KRY_STR_MAX_VSPRINTF_BUF_SIZE];
    vsprintf(buf, fmt, args);
    size_t buf_len = strlen(buf);

    if (buf_len >= meta->cap) {
      dest = kry_string_resize_cap(dest, buf_len + 1);
    }
    meta->len = buf_len;

    dest = (char*)meta + sizeof(kry_string_meta_t);
    strncpy(dest, buf, buf_len);
    dest[meta->len] = '\0';

    return dest;
  }

  return kry_string_vcreate(fmt, args);
}

kry_string_t kry_string_vappend(kry_string_t dest, const char* fmt,
                                va_list args)
{
  if (dest != NULL) {
    kry_string_meta_t* meta = kry_string_meta(dest);

    char buf[KRY_STR_MAX_VSPRINTF_BUF_SIZE];
    vsprintf(buf, fmt, args);

    size_t buf_len = strlen(buf);
    size_t old_len = meta->len;
    meta->len = buf_len + meta->len;

    if (meta->len >= meta->cap) {
      dest = kry_string_resize_cap(dest, meta->len + 1);
    }

    dest = (char*)meta + sizeof(kry_string_meta_t);
    strncpy(dest + old_len, buf, buf_len);
    dest[meta->len] = '\0';
    return dest;
  }

  return kry_string_vcreate(fmt, args);
}
