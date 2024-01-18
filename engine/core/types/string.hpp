/**
 * @file string.hpp
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

#ifndef KRYOS__CORE_TYPES__STRING_HPP
#define KRYOS__CORE_TYPES__STRING_HPP

#include <limits>

namespace kryos {

class String {
public:
    static constexpr size_t no_pos = std::numeric_limits<size_t>::max();

    template <typename... TArgs>
    static String format(const char* fmt, TArgs... args);

public:
    ~String();
    String() = default;
    String(const String& str);
    String(String&& str);
    String(const char* str);
    String(const char* str, size_t len);

public:
    bool operator==(const String& str) const;
    bool operator==(const char* str) const;

    String& operator=(const String& str);
    String& operator=(String&& str);
    String& operator=(const char* str);

    String operator+(const String& str);
    String operator+(const char* str);

    char& operator[](const size_t pos);
    const char operator[](const size_t pos) const;

public:
    inline char* data() const { return m_data; }
    inline const char* c_str() const { return m_data; }
    inline const size_t length() const { return m_len; }

    bool compare(const String& str) const;
    bool compare(const char* str, size_t len = no_pos) const;

    void copy(const String& str);
    void copy(const char* str, size_t len = no_pos);

    void append(const String& str);
    void append(const char* str, size_t len = no_pos);

    void clear();

private:
    char* m_data = nullptr;
    size_t m_len = 0;
};

template <typename... TArgs>
String String::format(const char* fmt, TArgs... args) {
}

} // namespace kryos
#endif
