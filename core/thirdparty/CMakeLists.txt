cmake_minimum_required(VERSION 3.20)
include(FetchContent)

FetchContent_Declare(glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG master)
FetchContent_Declare(cglm
    GIT_REPOSITORY https://github.com/recp/cglm.git
    GIT_TAG master)
FetchContent_MakeAvailable(glfw cglm)

add_library(
    glad STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/include/glad/glad.h
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/include/KHR/khrplatform.h
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glad/include)

set(kryos_core_thirdparty_include_dirs
    PRIVATE
    ${glfw_SOURCE_DIR}/include
    ${cglm_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/include
    CACHE INTERNAL "")

append_global_property(kryos_engine_libraries glad glfw cglm)
