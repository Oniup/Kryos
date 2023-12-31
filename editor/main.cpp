/**
 * @file main.cpp
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
#include <cstdio>
#include <cstring>

int main(int argc, char** argv)
{
  const char* lhs_str = "This is a test";
  const char* rhs_str = ", Appending this str";
  size_t lhs_length = std::strlen(lhs_str);
  size_t rhs_length = std::strlen(rhs_str);

  bool first = true;
  for (size_t i = 0; i < 1000; i++) {
    char* str = (char*)kryos::memory::malloc(lhs_length + 1);
    strncpy(str, lhs_str, lhs_length);
    str[lhs_length] = '\0';
    if (first) {
      std::printf("%s\n", str);
    }

    size_t length = lhs_length + rhs_length;
    str = (char*)kryos::memory::realloc(str, length + 1);
    strncpy(str + lhs_length, rhs_str, rhs_length);
    str[length] = '\0';
    if (first) {
      std::printf("%s\n", str);
    }

    first = false;
    kryos::memory::free(str);
  }
  return 0;
}
