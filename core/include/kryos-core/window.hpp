/* ------------------------------------------------------------------------ *
 * This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine) *
 * @file window.hpp                                                         *
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

#ifndef KRYOS__CORE__WINDOW_HPP
#define KRYOS__CORE__WINDOW_HPP

// #include "kryos-tools/containers/array_list.hpp"
// #include "kryos-tools/defines.hpp"
// #include <glm/glm.hpp>
//
// static bool _kint_glfw_init = false;
// static bool _kint_glad_init = false;
//
// typedef enum window_mode {
//     WINDOW_MODE_WINDOWED,
//     WINDOW_MODE_BORDERLESS_WINDOWED,
//     WINDOW_MODE_FULLSCREEN,
// } window_mode_t;
//
// typedef struct enabled_window_features {
//     bool vsync;
//     bool transparent_buffer;
//     bool resizable;
//     bool fullscreen;
// } enabled_window_features_t;
//
// typedef struct window_handle_create_options {
//     const char* title;
//     i32 width;
//     i32 height;
//     enabled_window_features_t enabled;
//     window_mode_t mode;
// } window_handle_create_options_t;
//
// typedef struct window_handle {
//     struct GLFWwindow* p_instance;
//     window_mode_t mode;
//     enabled_window_features_t enabled;
// } window_handle_t;
//
// typedef struct window_manager {
//     ARRAY_LIST(window_handle_t) p_handles;
// } window_manager_t;
//
// window_manager_t create_window_manager(const window_handle_create_options_t* p_handles_options,
//                                        usize count);
//
// void destroy_window_manager(window_manager_t* p_manager);
// void destroy_window_handle(window_handle_t* p_handle);
//
// window_handle_t* add_window_handle(window_manager_t* p_manager,
//                                    window_handle_create_options_t handle_options);
//
// bool continue_window_manager_runloop(window_manager_t* p_manager);
// void update_window_handles_frames(window_manager_t* p_manager);
//
// void set_window_handle_title(window_handle_t* handle, const char* title);
//
// const char* get_window_handle_title(window_handle_t* handle);
// void get_window_handle_size(window_handle_t* handle, glm::ivec2 size);
//
// /**
//  * @brief Retrieves the size of the frame of the window. This function retrieves the size, in screen
//  * coordinates, of each edge of the frame of the specified window. This size includes the title bar,
//  * if the window has one.
//  *
//  * @errors Possible errors include @ref GLFW_NOT_INITIALIZED and @ref GLFW_PLATFORM_ERROR.
//  * @thread_safety This function must only be called from the main thread.
//  *
//  * @param[in] handle The window whose frame size to query.
//  * @param[out] size Index 1 is the left, 2: top, 3: left, 4: bottom coordinates
//  */
// void get_window_handle_frame_size(window_handle_t* handle, glm::ivec4 size);

#endif
