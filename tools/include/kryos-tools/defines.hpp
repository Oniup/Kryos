/* ------------------------------------------------------------------------ *
 * This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine) *
 * @file defines.hpp                                                        *
 * ------------------------------------------------------------------------ *
 * @copyright (c) 2024 Oniup (https://github.com/Oniup)                     *
 *                                                                          *
 * Licensed under the Apache License, Version 2.0 (the "License");          *
 * you may not use this file except in compliance with the License.         *
 * You may obtain a copy of the License at                                  *
 *                                                                          *
 *   http://www.apache.org/licenses/LICENSE-2.0                             *
 *                                                                          *
 * Unless required by applicable law or agreed to in writing, software      *
 * distributed under the License is distributed on an "AS IS" BASIS,        *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. *
 * See the License for the specific language governing permissions and      *
 * limitations under the License.                                           *
 * ------------------------------------------------------------------------ */

#ifndef KRYOS__TOOLS__DEFINES_HPP
#define KRYOS__TOOLS__DEFINES_HPP

#if defined(_WIN32) || defined(__CYGWIN__)
    #ifdef KRYOS_WIN_EXPORT
        #ifdef __GNUC__
            #define KRYOS_API __attribute__((dllexport))
        #else
            #define KRYOS_API __declspec(dllexport)
        #endif
    #else
        #ifdef __GNUC__
            #define KRYOS_API __attribute__((dllimport))
        #else
            #define KRYOS_API __declspec(dllimport)
        #endif
    #endif
    #define NOT_KRYOS_API
#else
    #if __GNUC__ >= 4
        #define KRYOS_API __attribute__((visibility("default")))
        #define NOT_KRYOS_API __attribute__((visibility("hidden")))
    #else
        #define KRYOS_API
        #define NOT_KRYOS_API
    #endif
#endif

#include <cstdint>
#include <cstdio>

#define NO_ERROR_MESSAGE nullptr

#define KRYOS_VERSION_MAJOR 0u
#define KRYOS_VERSION_MINOR 0u
#define KRYOS_VERSION_PATCH 1u

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef size_t usize;

typedef float f32;
typedef double f64;

#endif
