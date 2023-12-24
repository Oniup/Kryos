/**
 * @file darray.c
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

#include "containers/darray.h"
#include "core/console.h"

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

void* darray_create(ui64_t stride, i32_t capacity)
{
  ui64_t header_size = sizeof(darray_header_t);
  ui64_t block_size = stride * capacity;
  ui64_t size = header_size + block_size;

  void* darray = malloc(size);
  KASSERT(darray,
          "Failed to malloc darray with block_size: %llu, total allocated "
          "size: %llu",
          block_size, size);

  darray_header_t* header = (darray_header_t*)darray;
  header->length = 0;
  header->capacity = capacity;
  header->stride = stride;

  return (ui8_t*)darray + header_size;
}

void darray_destroy(void* darray)
{
  if (darray != NULL) {
    void* ptr = (ui8_t*)darray - sizeof(darray_header_t);
    free(ptr);
  }
}

darray_header_t* darray_header_ptr(void* darray)
{
  KASSERT(darray, "Cannot get dynamic array header. darray == NULL");
  return (darray_header_t*)((ui8_t*)darray - sizeof(darray_header_t));
}

ui64_t darray_length(void* darray)
{
  return darray_header_ptr(darray)->length;
}

ui64_t darray_capacity(void* darray)
{
  return darray_header_ptr(darray)->capacity;
}

ui64_t darray_stride(void* darray)
{
  return darray_header_ptr(darray)->stride;
}

void* darray_set_length(void* darray, ui64_t length)
{
  darray_header_t* header = darray_header_ptr(darray);
  header->length = length;

  if (length >= header->capacity) {
    darray = darray_set_capacity(darray, length);
  }
  return darray;
}

void* darray_set_capacity(void* darray, ui64_t capacity)
{
  darray_header_t* header = darray_header_ptr(darray);
  ui64_t header_size = sizeof(darray_header_t);
  ui64_t block_size = header->stride * capacity;
  ui64_t size = header_size + block_size;

  darray_header_t* temp = (darray_header_t*)realloc(header, size);
  KASSERT(temp,
          "Failed to realloc darray with block_size: %llu, total allocated "
          "size: %llu",
          block_size, size);
  header = temp;
  header->capacity = capacity;

  darray = (ui8_t*)header + header_size;
  return darray;
}

void* darray_pop_back(void* darray, ui32_t count)
{
  return NULL;
}

void* darray_pop(void* darray, ui64_t index, ui32_t count)
{
  return NULL;
}

void* darray_copy_back(void* darray, void* value_ptr)
{
  darray_header_t* header = darray_header_ptr(darray);
  if (header->length + 1 >= header->capacity) {
    darray = darray_set_capacity(darray,
                                 header->capacity + KDEFAULT_CAP_INCREASE_SIZE);
    header = darray_header_ptr(darray);
  }

  memcpy((i8_t*)darray + header->stride * header->length, value_ptr,
         header->stride);
  header->length++;
  return darray;
}

void* darray_copy_array_back(void* darray, ui64_t count, void* array_ptr)
{
  return darray;
}

void* darray_copy_insert(void* darray, i64_t index, void* value_ptr)
{
  darray_header_t* header = darray_header_ptr(darray);
  if (header->length + 1 >= header->capacity) {
    darray = darray_set_capacity(darray,
                                 header->capacity + KDEFAULT_CAP_INCREASE_SIZE);
    header = darray_header_ptr(darray);
  }

  ui64_t rhs_len = (header->length - index) * header->stride;
  i8_t* darray_byte = (i8_t*)darray;
  memcpy(darray_byte + (index + 1) * header->stride,
         darray_byte + index * header->stride, rhs_len);
  memcpy(darray_byte + index, value_ptr, header->stride);
  return darray;
}

void* darray_copy_array_insert(void* darray, ui64_t index, ui64_t length,
                               void* array_ptr)
{
  return darray;
}
