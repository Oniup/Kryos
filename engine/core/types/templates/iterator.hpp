/**
 * @file iterator.hpp
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

#ifndef KRYOS__CORE_TYPES_TEMPLATES__ITERATOR_HPP
#define KRYOS__CORE_TYPES_TEMPLATES__ITERATOR_HPP

#include "core/log.hpp"

namespace kryos {

template <typename T>
struct iIterator {
public:
    iIterator() = default;

    iIterator(const iIterator& iter)
          : m_ptr(iter.m_ptr) {}

    iIterator(iIterator&& iter)
          : m_ptr(iter.m_ptr) {
        iter.m_ptr = nullptr;
    }

    inline T& operator*() {
        return *m_ptr;
    }

    inline T* operator->() {
        return m_ptr;
    }

    inline const T& operator*() const {
        KASSERT(m_ptr != nullptr, "Cannot get iterator value as reference. Pointer is null");
        return *m_ptr;
    }

    inline const T* operator->() const { return m_ptr; }

private:
    T* m_ptr {nullptr};
};

} // namespace kryos

#endif
