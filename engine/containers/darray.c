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

#include <stdio.h>
#include <stdlib.h>

void* darray_create(ui64_t size, i32_t cap)
{
  return NULL;
}

void darray_destroy(void* darray)
{
  if (darray != NULL) {
    void* ptr = (ui8_t*)darray - sizeof(darray_header_t);
    free(darray);
  }
}

darray_header_t* darray_header_ptr(void* darray)
{
  if (darray != NULL) {
    return (darray_header_t*)((ui8_t*)darray - sizeof(darray_header_t));
  }
  return NULL;
}
