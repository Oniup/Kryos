/* ------------------------------------------------------------------------ *
 * This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine) *
 * @file asset_manager.hpp                                                  *
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

#ifndef KRYOS__CORE__ASSET_MANAGER_HPP
#define KRYOS__CORE__ASSET_MANAGER_HPP

#include "kryos-tools/containers/array_list.hpp"
#include "kryos-tools/defines.hpp"

// #ifdef RENDERER_USE_OPENGL_BACKEND
//     #include "kryos-renderer/opengl/data_types.hpp"
//     #include "kryos-renderer/opengl/renderer.hpp"
// #endif
//
// typedef struct mesh {
//     ARRAY_LIST(vertex_t) vertices;
//     ARRAY_LIST(u32) indices;
//     material_t* material;
// } mesh_t;
//
// typedef struct model {
//     u64 uuid;
//     const char* name;
//     ARRAY_LIST(mesh_t) meshes;
// } model_t;
//
// typedef struct prefab {
//     u64 uuid;
//     const char* name;
//     ARRAY_LIST(model_t) models;
// } prefab_t;
//
// typedef struct managed_shader {
//     shader_t* p_shader;
// } managed_shader_t;
//
// typedef struct asset_manager {
//     renderer_context_t* context;
//     ARRAY_LIST(material_t) p_materials;
//     ARRAY_LIST(mesh_t) p_static_meshes;
// } asset_manager_t;
//
// asset_manager_t create_asset_manager();
// void destroy_asset_manager(asset_manager_t* p_asset_manager);
//
// typedef struct shader_source_info {
//     char* p_filename;
//     u8* p_code;
//     usize code_size;
//     shader_type_t type;
// } shader_source_info_t;

#ifdef KRYOS_EDITOR

shader_t load_managed_shader_asset(const char* p_shader_asset_filename);
b8 create_managed_shader_asset(const char* p_serialize_path, const char* name,
                               const shader_source_info_t* p_sources_create_info, usize count);
void unload_managed_shader_asset(const char* shader_name);

#endif

#endif
