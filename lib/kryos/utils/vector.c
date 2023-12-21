/**
 * @file vector.c
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

#include "utils/vector.h"
#include "core/console.h"

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

void* kry_vector_create(size_t type_size)
{
  void* vector = malloc(sizeof(kry_vector_meta_t) +
                        type_size * KRY_VECTOR_CAPACITY_INCREASE_SIZE);

  kry_vector_meta_t* meta = (kry_vector_meta_t*)vector;
  meta->length = 0;
  meta->capacity = KRY_VECTOR_CAPACITY_INCREASE_SIZE;
  meta->chunk = type_size;

  return (char*)vector + sizeof(kry_vector_meta_t);
}

void kry_vector_destroy(void* vector)
{
  if (vector != NULL) {
    char* ptr = (char*)vector - sizeof(kry_vector_meta_t);
    free(ptr);
  }
}

kry_vector_meta_t* kry_vector_meta(void* vector)
{
  return (kry_vector_meta_t*)((char*)vector - sizeof(kry_vector_meta_t));
}

size_t kry_vector_len(void* vector)
{
  return kry_vector_meta(vector)->length;
}

size_t kry_vector_cap(void* vector)
{
  return kry_vector_meta(vector)->capacity;
}

size_t kry_vector_chunk_size(void* vector)
{
  return kry_vector_meta(vector)->chunk;
}

void* kry_vector_set_len(void* vector, size_t len)
{
  kry_vector_meta_t* meta = kry_vector_meta(vector);
  // PERF: Can be optimized. This is temporary
  while (len > meta->capacity) {
    vector = kry_vector_set_cap(vector, meta->capacity +
                                            KRY_VECTOR_CAPACITY_INCREASE_SIZE);
    meta = kry_vector_meta(vector);
  }
  meta->length = len;
  return (char*)meta + sizeof(kry_vector_meta_t);
}

void* kry_vector_set_cap(void* vector, size_t cap)
{
  kry_vector_meta_t* meta = kry_vector_meta(vector);
  meta = (kry_vector_meta_t*)realloc((void*)meta, sizeof(kry_vector_meta_t) +
                                                      cap * meta->chunk);
  KRY_ASSERT(meta, "Failed to increase vector capacity to %zu", cap);
  meta->capacity = cap;
  return (char*)meta + sizeof(kry_vector_meta_t);
}

void* kry_vector_copy_into_chunk(void* vector, size_t index, void* lvalue)
{
  kry_vector_meta_t* meta = kry_vector_meta(vector);
  void* result = memcpy(vector + index * meta->chunk, lvalue, meta->chunk);
  KRY_ASSERT(result, "Failed to memcpy lvalue int chunk %z", index);
  return result;
}
