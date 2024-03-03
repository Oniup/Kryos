/* ------------------------------------------------------------------------ *
 * This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine) *
 * @file window.h                                                           *
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

#ifndef KRYOS__CORE__WINDOW_H
#define KRYOS__CORE__WINDOW_H
#ifdef __cplusplus
extern "C" {
#endif

#include "kryos-tools/containers/array_list.h"
#include "kryos-tools/defines.h"

static b8 _kint_glfw_init = false;
static b8 _kint_glad_init = false;

typedef enum window_mode {
    WINDOW_MODE_WINDOWED,
    WINDOW_MODE_BORDERLESS_WINDOWED,
    WINDOW_MODE_FULLSCREEN,
} window_mode_t;

typedef struct enabled_window_features {
    b8 vsync;
    b8 transparent_buffer;
    b8 resizable;
    b8 fullscreen;
} enabled_window_features_t;

typedef struct window_create_options {
    const char* title;
    i32 width;
    i32 height;
    enabled_window_features_t enabled;
    window_mode_t mode;
} window_create_options_t;

typedef struct window_handle {
    struct GLFWwindow* p_instance;
    window_mode_t mode;
    enabled_window_features_t enabled;
} window_handle_t;

typedef struct window_manager {
    ARRAY_LIST(window_handle_t) p_handles;
} window_manager_t;

window_manager_t create_window_manager(const window_create_options_t* p_handles_options,
                                       usize count);

void destroy_window_manager(window_manager_t* p_manager);
void destroy_window_handle(window_handle_t* p_handle);

window_handle_t* add_window_handle(window_manager_t* p_manager,
                                   window_create_options_t handle_options);

b8 continue_window_manager_runloop(window_manager_t* p_manager);
void update_window_handles_frames(window_manager_t* p_manager);

#ifdef __cplusplus
}
#endif
#endif
