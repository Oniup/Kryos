/// ------------------------------------------------------------------------ ///
/// This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine) ///
/// @file define.h                                                           ///
/// ------------------------------------------------------------------------ ///
/// @copyright (c) 2024 Oniup (https://github.com/Oniup)                     ///
///                                                                          ///
/// Licensed under the Apache License, Version 2.0 (the "License");          ///
/// you may not use this file except in compliance with the License.         ///
/// You may obtain a copy of the License at                                  ///
///                                                                          ///
///   http://www.apache.org/licenses/LICENSE-2.0                             ///
///                                                                          ///
/// Unless required by applicable law or agreed to in writing, software      ///
/// distributed under the License is distributed on an "AS IS" BASIS,        ///
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. ///
/// See the License for the specific language governing permissions and      ///
/// limitations under the License.                                           ///
/// ------------------------------------------------------------------------ ///

#ifndef KRYOS__TOOLS__DEFINES_H
#define KRYOS__TOOLS__DEFINES_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>

#if defined(KRYOS_BUILD_SHARED) && defined(KRYOS_DLL)
    #error \
        "Cannot have both 'KRYOS_BUILD_SHARED' and 'KRYOS_DLL' at the same time, only either or none"
#endif

#if defined(_WIN32) && defined(KRYOS_BUILD_SHARED)
    #define KRYAPI __declspec(dllexport)
#elif defined(_WIN32) && defined(KRYOS_DLL)
    #define KRYAPI __declspec(dllimport)
#elif defined(__GNUC__) && defined(KRYOS_BUILD_SHARED)
    #define KRYAPI __attribute__((visibility("default")))
#else
    #define KRYAPI
#endif

#define KRYOS_VERSION_MAJOR 0u
#define KRYOS_VERSION_MINOR 0u
#define KRYOS_VERSION_PATCH 1u

#define I8_MAX INT8_MAX
#define I8_MIN INT8_MIN
#define I16_MAX INT16_MAX
#define I16_MIN INT16_MIN
#define I32_MAX INT32_MAX
#define I32_MIN INT32_MIN
#define I64_MAX INT64_MAX
#define I64_MIN INT64_MIN

#define USIZE_MAX SIZE_MAX

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

typedef int8_t b8;
#define true 1
#define false 0

#ifdef __cplusplus
extern "C" {
#endif
#endif
