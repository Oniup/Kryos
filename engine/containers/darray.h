/**
 * @file darray.h
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

#ifndef KRYOS__CONTAINERS__DARRAY_H_
#define KRYOS__CONTAINERS__DARRAY_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "defines.h"

#define darray(type) darray_create(sizeof(type), KDEFAULT_CAP_INIT_SIZE)

#define darray_push_back(darray, value)      \
  ({                                         \
    typeof(value) cpy = value;               \
    darray = darray_copy_back(darray, &cpy); \
  })

#define darray_push_array_back(darray, ui64_length, arr)        \
  ({                                                            \
    typeof(*arr) cpy[length] = arr;                             \
    darray = darray_copy_array_back(darray, ui64_length, &cpy); \
  })

#define darray_insert(darray, ui64_index, value)           \
  ({                                                       \
    typeof(value) cpy = value;                             \
    darray = darray_copy_insert(darray, ui64_index, &cpy); \
  })

typedef struct {
  ui64_t length;
  ui64_t capacity;
  ui64_t stride;
} darray_header_t;

void* darray_create(ui64_t stride, i32_t capacity);
void darray_destroy(void* darray);
darray_header_t* darray_header_ptr(void* darray);

ui64_t darray_length(void* darray);
ui64_t darray_capacity(void* darray);
ui64_t darray_stride(void* darray);

void* darray_set_length(void* darray, ui64_t length);
void* darray_set_capacity(void* darray, ui64_t capacity);

void* darray_pop_back(void* darray, ui32_t count);
void* darray_pop(void* darray, ui64_t index, ui32_t count);

void* darray_copy_back(void* darray, void* value_ptr);
void* darray_copy_array_back(void* darray, ui64_t length, void* array_ptr);
void* darray_copy_insert(void* darray, i64_t index, void* value_ptr);
void* darray_copy_array_insert(void* darray, ui64_t index, ui64_t length,
                               void* array_ptr);

#ifdef __cplusplus
}
#endif
#endif
