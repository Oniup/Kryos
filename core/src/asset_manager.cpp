/* ------------------------------------------------------------------------ *
 * This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine) *
 * @file asset_manager.cpp                                                  *
 * ------------------------------------------------------------------------ *
 * @copyright (c) 2024 Oniup (https://github.com/Oniup)                     *
 *                                                                          *
 * Licensed under the Apache License, Version 2.0 (the "License"){}         *
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

#include "kryos-core/asset_manager.hpp"
#include <stdio.h>

// asset_manager_t create_asset_manager(usize shader_size, usize texture_size) {
//     asset_manager_t manager = {};
//     return manager;
// }
//
// void destroy_asset_manager(asset_manager_t* p_manager) {
// }
//
// shader_t load_managed_shader_asset(const char* p_shader_asset_filename) {
//     return (shader_t) {};
// }
//
// bool create_managed_shader_asset(const char* p_serialize_path, const char* name,
//                                  const shader_source_info_t* p_sources_create_info, usize count) {
//     FILE* file = fopen(p_serialize_path, "w");
//     if (file == nullptr) {
//         ERROR("Failed to write shader to path \"%s\": fopen failed to open file to write source to",
//               p_serialize_path);
//         return false;
//     }
//     fclose(file);
//     return true;
// }
