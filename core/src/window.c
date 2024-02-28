/// ------------------------------------------------------------------------ ///
/// This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine) ///
/// @file window.h                                                           ///
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

#include "kryos-core/window.h"
#include "kryos-tools/containers/array_list.h"
#include <stdlib.h>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

window_manager_t create_window_manager(const window_create_options_t* p_handles_options,
                                       usize count) {
    if (!_kint_glfw_init) {
        i32 glfw_init_result = glfwInit();
        ASSERT(glfw_init_result, "Failed to initialize glfw. Required for Kryos engine to run");
        _kint_glfw_init = true;
    }
    window_manager_t manager = {
        .p_handles = create_array_list(window_handle_t),
    };
    for (usize i = 0; i < count; i++) {
        window_handle_t handle = add_window_handle(&manager, p_handles_options[i]);
        if (handle.p_instance != NULL) {
            ERROR("Failed to create window handle %s for index %zu", p_handles_options[i].title, i);
            continue;
        }
    }
    return manager;
}

void destroy_window_manager(window_manager_t* p_manager) {
    usize count = get_array_list_size(p_manager->p_handles);
    for (usize i = 0; i < count; i++) {
        destroy_window_handle(&p_manager->p_handles[i]);
    }
    p_manager->p_handles = NULL;
    glfwTerminate();
    _kint_glfw_init = false;
    _kint_glad_init = false;
}

void destroy_window_handle(window_handle_t* p_handle) {
    glfwDestroyWindow(p_handle->p_instance);
    p_handle->p_instance = NULL;
}

window_handle_t add_window_handle(window_manager_t* p_manager,
                                  window_create_options_t handle_options) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if (handle_options.enabled.transparent_buffer) {
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    }
    if (!handle_options.enabled.resizable) {
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    }
    GLFWwindow* p_main = NULL;
    if (get_array_list_size(p_manager->p_handles)) {
        p_main = p_manager->p_handles[0].p_instance;
    }
    GLFWwindow* p_instance = NULL;
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* video_mode = glfwGetVideoMode(monitor);
    switch (handle_options.mode) {
        case WINDOW_MODE_WINDOWED:
            p_instance = glfwCreateWindow(handle_options.width, handle_options.height,
                                          handle_options.title, NULL, p_main);
            break;
        case WINDOW_MODE_BORDERLESS_WINDOWED:
            glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
            p_instance = glfwCreateWindow(video_mode->width, video_mode->height,
                                          handle_options.title, NULL, p_main);
            break;
        case WINDOW_MODE_FULLSCREEN:
            p_instance = glfwCreateWindow(handle_options.width, handle_options.height,
                                          handle_options.title, monitor, p_main);
            break;
    }
    if (p_instance == NULL) {
        ERROR("Failed to create window handle with title \"%s\"", handle_options.title);
        return (window_handle_t) {.p_instance = NULL};
    }
    if (!_kint_glad_init) {
        i32 glad_init_result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        ASSERT(glad_init_result,
               "Failed to load opengl through glad, this is required for kryos engine to run");
        _kint_glad_init = true;
    }
    return (window_handle_t) {
        .p_instance = p_instance,
        .enabled = handle_options.enabled,
        .mode = handle_options.mode,
    };
}