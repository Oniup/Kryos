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

#include "core/console.h"
#include "defines.h"
#include "engine/containers/darray.h"
#include "engine/containers/string.h"
#include "engine/core/context.h"

#include <stdio.h>

typedef struct {
  char* text;
  ui32_t integer;
  float floating_point;
} test_data_t;

test_data_t test_data_create(char* text, ui32_t integer, float floating_point)
{
  test_data_t result = {
      .text = text,
      .integer = integer,
      .floating_point = floating_point,
  };
  return result;
}

void print_darray_result(const char* name, test_data_t* darray, b8_t first)
{
  if (first) {
    darray_header_t* header = darray_header_ptr(darray);
    char* result = string_create("%s:\ntest_data_t* darray = {\n", name);
    for (ui64_t i = 0; i < darray_length(darray); i++) {
      result = string_append(result, "  { \"%s\", %u, %f }\n", darray[i].text,
                             darray[i].integer, darray[i].floating_point);
    }
    result = string_append(result, "}");
    KTRACE(result);
  }
}

int main(int argc, char** argv)
{
  context_init();
  b8_t first = true;

  KDEBUG("Testing Strings");
  for (ui64_t i = 0; i < 1000; i++) {
    char* str = string_create("This is a test string at i %llu.", i);
    if (first) {
      KTRACE(str);
    }
    str = string_append(
        str, " Some string appended at the end of the original string");
    if (first) {
      KTRACE(str);
    }
    str = string_copy(str, "Replaced original string with copied string");
    if (first) {
      KTRACE(str);
    }
    first = false;
  }

  first = true;
  KDEBUG("Testing darray");
  for (ui64_t i = 0; i < 1000; i++) {
    test_data_t* darray = darray(test_data_t);

    darray_push_back(darray, test_data_create("This is a test", 1, 5 * 2.0f));
    darray_push_back(darray, test_data_create("Another Entry", 2, 2 * 3.0f));
    darray_push_back(darray,
                     test_data_create("Last push back entry", 3, 420.0f));
    print_darray_result("darray_push_back", darray, first);

    // FIX: inserting results in a segment fault
    // darray_insert(darray, 1,
    //               test_data_create("Inserted", 123, 123.0f * 123.0f));
    // print_darray_result("darray_insert", darray, first);

    darray_destroy(darray);

    first = false;
  }

  context_terminate();
}
