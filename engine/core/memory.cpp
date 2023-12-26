/**
 * @file memory.cpp
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

#include "core/memory.hpp"

#include <assert.h>
#include <stdlib.h>

namespace kryos {

ui32_t MemoryHeader::get_ref_count(void* ptr)
{
  MemoryHeader* header = (MemoryHeader*)ptr - 1;
  return header->ref_count;
}

void* Allocator::allocate_memory(ui64_t stride, ui64_t count, bool prepad)
{
  ui64_t block_size = stride * count;
  void* ptr = malloc(prepad ? block_size + sizeof(MemoryHeader) : block_size);
  assert(ptr && "malloc failed");
  if (prepad) {
    MemoryHeader* header = (MemoryHeader*)ptr;
    header->ref_count = 1;
    header->block_size = block_size;
    ptr = header + 1;
  }
  return ptr;
}

void* Allocator::reallocate_memory(void* ptr, ui64_t stride, ui64_t count,
                                   bool prepad)
{
  ui64_t block_size = stride * count;
  void* temp = nullptr;
  if (prepad) {
    temp = realloc((MemoryHeader*)ptr - 1, block_size + sizeof(MemoryHeader));
    assert(temp && "realloc failed for block with prepad");
    MemoryHeader* header = (MemoryHeader*)temp;
    header->block_size = block_size;
    ptr = header + 1;
  }
  else {
    temp = realloc(ptr, block_size);
    assert(temp && "realloc failed");
    temp = ptr;
  }
  return ptr;
}

void Allocator::free_memory(void* ptr, bool prepad)
{
  if (prepad) {
    MemoryHeader* header = (MemoryHeader*)ptr - 1;
    header->ref_count--;
    if (header->ref_count < 1) {
      free(ptr);
    }
  }
  else {
    free(ptr);
  }
}

} // namespace kryos
