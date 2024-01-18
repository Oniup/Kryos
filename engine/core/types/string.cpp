/**
 * @file string.cpp
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

#include "core/types/string.hpp"
#include "core/memory.hpp"

#include <string.h>

namespace kryos {

String::~String() {
    clear();
}

String::String(const String& str)
      : String(str.m_data, str.m_len) {
}

String::String(String&& str)
      : m_data(str.m_data), m_len(str.m_len) {
    str.m_data = nullptr;
    str.m_len = no_pos;
}

String::String(const char* str)
      : m_data(), m_len(strlen(str)) {
    strncpy(m_data, str, m_len);
    m_data[m_len] = 0;
}

String::String(const char* str, size_t len)
      : m_data(), m_len(len) {
    strncpy(m_data, str, m_len);
}

bool String::compare(const String& str) const {
    return compare(str.m_data, str.m_len);
}

bool String::compare(const char* str, size_t len) const {
    if (len == m_len) {
        if (str == m_data) {
            return true;
        }
        return strncmp(m_data, str, len);
    }
    return false;
}

void String::copy(const String& str) {
    copy(str.m_data, str.m_len);
}

void String::copy(const char* str, size_t len) {
    clear();
    if (len == no_pos || len < 1) {
        len = strlen(str);
    }
}

void String::append(const String& str) {
}

void String::append(const char* str, size_t len) {
}

void String::clear() {
}

} // namespace kryos
