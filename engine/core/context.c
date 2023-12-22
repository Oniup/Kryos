/**
 * @file context.c
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

#include "core/context.h"
#include "defines.h"

#include <stdio.h>
#include <stdlib.h>

engine_context_t* g_context = NULL;

engine_context_t* context_ptr()
{
  return g_context;
}

void context_init()
{
  g_context = (engine_context_t*)malloc(sizeof(engine_context_t));

  g_context->console.output_file = "debug.log";
  g_context->console.callback = NULL;
  g_context->console.filter = CONSOLE_SEVERITY_NONE_BIT;
}

void context_terminate()
{
  free(g_context);
  g_context = NULL;
}
