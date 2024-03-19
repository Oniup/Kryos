/* ------------------------------------------------------------------------ *
 * This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine) *
 * @file engine_context.hpp                                                 *
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

#ifndef KRYOS__CORE__ENGINE_CONTEXT_H
#define KRYOS__CORE__ENGINE_CONTEXT_H

#include "kryos-core/asset_manager.hpp"
#include "kryos-core/window.hpp"

typedef enum graphics_backend {
    RENDERER_API_BACKEND_OPENGL,
    RENDERER_API_BACKEND_WEBGL,
    RENDERER_API_BACKEND_VULKAN,
} graphics_backend_t;

typedef struct engine_context {
    graphics_backend_t graphics_backend;
} engine_context_t;

#endif
