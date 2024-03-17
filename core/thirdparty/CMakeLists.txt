cmake_minimum_required(VERSION 3.20)
include(FetchContent)

FetchContent_Declare(glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG master)
FetchContent_Declare(cglm
    GIT_REPOSITORY https://github.com/recp/cglm.git
    GIT_TAG master)
FetchContent_MakeAvailable(glfw cglm)

set(kryos_core_thirdparty_include_dirs
    PRIVATE
    ${glfw_SOURCE_DIR}/include/
    ${cglm_SOURCE_DIR}/include/
    CACHE INTERNAL "")

append_global_property(kryos_engine_include_dirs ${kryos_core_thirdparty_include_dirs})
append_global_property(kryos_engine_libraries glfw cglm)
