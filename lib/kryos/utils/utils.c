/**
 * @file utils.c
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

#include "utils/utils.h"

const char* kry_ansi_col(const char indent)
{
  switch (indent) {
  case 'r':
    return KRY_ANSI_COL_RED;
  case 'g':
    return KRY_ANSI_COL_GREEN;
  case 'y':
    return KRY_ANSI_COL_YELLOW;
  case 'b':
    return KRY_ANSI_COL_BLUE;
  case 'm':
    return KRY_ANSI_COL_MAGENTA;
  case 'c':
    return KRY_ANSI_COL_CYAN;
  case 'w':
    return KRY_ANSI_COL_WHITE;
  case 'e':
    return KRY_ANSI_COL_GREY;
  case 'R':
    return KRY_ANSI_COL_B_RED;
  case 'G':
    return KRY_ANSI_COL_B_GREEN;
  case 'Y':
    return KRY_ANSI_COL_B_YELLOW;
  case 'B':
    return KRY_ANSI_COL_B_BLUE;
  case 'M':
    return KRY_ANSI_COL_B_MAGENTA;
  case 'C':
    return KRY_ANSI_COL_B_CYAN;
  case 'W':
    return KRY_ANSI_COL_B_WHITE;
  default:
    return KRY_ANSI_COL_DEFAULT;
  }
}

const char* kry_ansi_hl_col(const char indent)
{
  switch (indent) {
  case 'r':
    return KRY_ANSI_COL_HL_RED;
  case 'g':
    return KRY_ANSI_COL_HL_GREEN;
  case 'y':
    return KRY_ANSI_COL_HL_YELLOW;
  case 'b':
    return KRY_ANSI_COL_HL_BLUE;
  case 'm':
    return KRY_ANSI_COL_HL_MAGENTA;
  case 'c':
    return KRY_ANSI_COL_HL_CYAN;
  case 'w':
    return KRY_ANSI_COL_HL_WHITE;
  case 'e':
    return KRY_ANSI_COL_HL_GREY;
  case 'R':
    return KRY_ANSI_COL_BHL_RED;
  case 'G':
    return KRY_ANSI_COL_BHL_GREEN;
  case 'Y':
    return KRY_ANSI_COL_BHL_YELLOW;
  case 'B':
    return KRY_ANSI_COL_BHL_BLUE;
  case 'M':
    return KRY_ANSI_COL_BHL_MAGENTA;
  case 'C':
    return KRY_ANSI_COL_BHL_CYAN;
  case 'W':
    return KRY_ANSI_COL_BHL_WHITE;
  default:
    return KRY_ANSI_COL_DEFAULT;
  }
}
