/* ------------------------------------------------------------------------ *
 * This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine) *
 * @file data_types.hpp                                                     *
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

#ifndef KRYOS__RENDERER__OPENGL_DATA_TYPES_HPP
#define KRYOS__RENDERER__OPENGL_DATA_TYPES_HPP
#ifdef RENDERER_USE_OPENGL_BACKEND

    #include "kryos-tools/containers/array_list.hpp"
    #include "kryos-tools/defines.hpp"
    #include <cglm/cglm.h>

typedef enum shader_type {
    SHADER_TYPE_VERTEX,
    SHADER_TYPE_FRAGMENTED,
    SHADER_TYPE_GEOMETRY,
    SHADER_TYPE_COMPUTE,
} shader_type_t;

typedef struct shader {
    u64 uuid;
    char* p_name;
    struct {
        u32 program_id;
    } gl;
} shader_t;

shader_t create_shader(const char* name, const u8* pp_sources[], const shader_type_t* p_types,
                       usize count);
void destroy_shader(shader_t* p_shader);

typedef struct texture {
    u64 uuid;
    char* p_name;
    i32 width;
    i32 height;
    i32 channels;
} texture_t;

typedef struct texture_image_data {
    texture_t texture;
    u8* p_image_data;
} textexture_iamge_datature_image_data_t;

typedef struct material {
    u64 uuid;
    char* p_name;
    ARRAY_LIST(texture_t*) textures;
} material_t;

typedef struct vertex {
    vec3 position;
    vec3 normal;
    vec4 color_tint;
    vec2 uv;
} vertex_t;

#endif
#endif
