/**
 * @file vector.h
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

#ifndef KRYOS__UTILS__VECTOR_H_
#define KRYOS__UTILS__VECTOR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#define KRY_VECTOR_CAPACITY_INCREASE_SIZE 20

#define KRY_VECTOR_PUSH_BACK(vector, rvalue)      \
  ({                                              \
    size_t len = kry_vector_len(vector);          \
    vector = kry_vector_set_len(vector, len + 1); \
    vector[len] = rvalue;                         \
  })

#define KRY_VECTOR_COPY_BACK(vector, lvalue)         \
  ({                                                 \
    size_t pos = kry_vector_len(vector);             \
    vector = kry_vector_set_len(vector, pos + 1);    \
    kry_vector_copy_into_chunk(vector, pos, lvalue); \
  })

typedef struct kry_vector_meta {
  size_t length;
  size_t capacity;
  size_t chunk;
} kry_vector_meta_t;

void* kry_vector_create(size_t type_size);
void kry_vector_destroy(void* vector);
kry_vector_meta_t* kry_vector_meta(void* vector);

size_t kry_vector_len(void* vector);
size_t kry_vector_cap(void* vector);
size_t kry_vector_chunk_size(void* vector);

void* kry_vector_set_len(void* vector, size_t len);
void* kry_vector_set_cap(void* vector, size_t cap);
void* kry_vector_copy_into_chunk(void* vector, size_t index, void* lvalue);

#ifdef __cplusplus
}
#endif

#endif
