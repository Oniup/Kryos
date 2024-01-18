/**
 * @file memory.hpp
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

#ifndef KRYOS__CORE__MEMORY_HPP
#define KRYOS__CORE__MEMORY_HPP

#include "core/log.hpp"
#include "core/types/templates/option.hpp"

#include <memory.h>
#include <type_traits>

namespace kryos {

using MemOpt = Opt<void*>;

void mem_free(void* ptr);
MemOpt mem_alloc(size_t size);
MemOpt mem_realloc(void* ptr, size_t size);
MemOpt mem_realloc_insert(void* ptr, size_t size, size_t pos, size_t insert_size);

template <typename T>
constexpr std::remove_reference_t<T>&& mem_move(T&& value) noexcept {
    return static_cast<std::remove_reference_t<T>&&>(value);
}

template <typename T>
constexpr bool mem_copy(T* beg, T* end, const T* src) {
    const size_t len = end - beg;
    if constexpr (std::is_class_v<T> && std::is_trivially_copy_constructible_v<T>) {
        for (size_t i = 0; i < len; i++) {
            new (beg[i]) T(src[i]);
        }
        return true;
    } else if (std::is_class_v<T> && std::is_trivially_copyable_v<T>) {
        for (size_t i = 0; i < len; i++) {
            beg[i] = src[i];
        }
        return true;
    } else if (std::is_trivially_copyable_v<T>) {
        // KASSERT(memcpy(beg, src, sizeof(T) * len), "Failed to memcpy insert data");
        return memcpy(beg, src, sizeof(T) * len) != nullptr;
    }
    // KASSERT(false, "Cannot mem_copy/mem_insert, type is not trivially copyable");
    return false;
}

template <typename T>
constexpr Opt<T*> mem_copy_insert(T* beg, T* end, const T* src_beg, const T* src_end, size_t pos) {
    const size_t len = end - beg;
    const size_t src_len = src_end - src_beg;
    MemOpt opt = mem_realloc_insert(beg, sizeof(T) * len, sizeof(T) * pos, sizeof(T) * src_len);
    if (opt.status() == OptState::ok) {
        beg = static_cast<T*>(opt.value());
        if (mem_copy(beg + pos, beg + (pos + src_len), src_beg)) {
            return Opt<T*>::some(beg);
        }
    }
    return Opt<T*>::failed(beg);
}

} // namespace kryos

#endif
