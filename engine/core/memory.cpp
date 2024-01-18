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

#include <stdlib.h>

namespace kryos {

void mem_free(void* ptr) {
    if (ptr != nullptr) {
        free(ptr);
    }
}

MemOpt mem_alloc(size_t size) {
    void* ptr = malloc(size);
    if (ptr != nullptr) {
        return MemOpt::some(ptr);
    }
    // KASSERT(ptr, "Failed to malloc system memory for size %zu", size);
    return MemOpt::none();
}

MemOpt mem_realloc(void* ptr, size_t size) {
    if (ptr != nullptr) {
        void* tmp = nullptr;
        tmp = realloc(ptr, size);
        if (tmp != nullptr) {
            return MemOpt::some(tmp);
        }
        // KASSERT(tmp, "Failed to realloc system memory for size %zu at address %p", size, ptr);
        return MemOpt::failed(ptr);
    }
    return mem_alloc(size);
}

MemOpt mem_realloc_insert(void* ptr, size_t size, size_t pos, size_t insert_size) {
    const size_t full_size = size + insert_size;
    if (size == pos) {
        return mem_realloc(ptr, full_size);
    }
    MemOpt opt = mem_realloc(ptr, full_size);
    if (opt.status() == OptState::ok) {
        const size_t chunk_size = size - pos;
        ptr = opt.value();
        if (memcpy((char*)ptr + (pos + insert_size), (char*)ptr + pos, chunk_size) != nullptr) {
            return MemOpt::some(ptr);
        }
        // "Failed to memcpy data to make room for insert"
        return opt;
    }
    return opt;
}

} // namespace kryos
