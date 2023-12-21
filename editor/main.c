/**
 * @file main.c
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

#include "engine/containers/string.h"
#include "engine/core/context.h"

#include <stdbool.h>
#include <string.h>

static bool first = true;

void print_result(string_t str)
{
  if (first) {
    string_header_t* header = string_header(str);
    KINFO("result: len: %zu, cap: %zu, strlen: %zu, str: \"%s\"\n", header->len,
          header->cap, strlen(str), str);
  }
}

int main(int argc, char** argv)
{
  context_init();

  for (size_t i = 0; i < 1000; i++) {
    string_t str =
        string_create("Example string: [%s], int: [%d]", "This is a test", 420);
    print_result(str);
    str = string_copy(str, "Copying str");
    print_result(str);
    for (size_t j = 0; j < 10; j++) {
      str = string_append(str, "...%zu", j);
    }
    print_result(str);

    string_destroy(str);
    first = false;
  }

  context_terminate();
}
