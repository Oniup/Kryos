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

#include "kryos/core/context.h"
#include "kryos/utils/string.h"

#include <stdbool.h>
#include <string.h>

static bool first = true;

void print_result(kry_string_t str)
{
  if (first) {
    kry_string_meta_t* meta = kry_string_meta(str);
    KRY_INFO("result: len: %zu, cap: %zu, strlen: %zu, str: \"%s\"\n",
             meta->len, meta->cap, strlen(str), str);
  }
}

int main(int argc, char** argv)
{
  kry_context_init();

  for (size_t i = 0; i < 1000; i++) {
    kry_string_t str = kry_string_create("Example string: [%s], int: [%d]",
                                         "This is a test", 420);
    print_result(str);
    str = kry_string_copy(str, "Copying str");
    print_result(str);
    for (size_t j = 0; j < 10; j++) {
      str = kry_string_append(str, "...%zu", j);
    }
    print_result(str);

    kry_string_destroy(str);
    first = false;
  }

  kry_context_terminate();
}
