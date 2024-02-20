/// ------------------------------------------------------------------------ ///
/// This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine) ///
/// @file dylist.h                                                           ///
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

#ifndef KRYOS__TOOLS__DYLIST_H
#define KRYOS__TOOLS__DYLIST_H
#ifdef __cplusplus
extern "C" {
#endif

#include "kryos-tools/defines.h"

#define create_dylist(T, count) intl_create_dylist(sizeof(T), count)

void* intl_create_dylist(usize type_size, usize count);
void* intl_push_back_dylist(void* p_dylist, usize type_size, usize count, void* p_data);
void* intl_push_front_dylist(void* p_dylist, usize type_size, usize count, void* p_data);
void* intl_insert_dylist(void* p_dylist, usize type_size, usize pos, usize count,
                         void* p_data);

#ifdef __cplusplus
}
#endif
#endif
