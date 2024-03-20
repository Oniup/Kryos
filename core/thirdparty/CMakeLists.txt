cmake_minimum_required(VERSION 3.20)
include(FetchContent)

fetch_dependency(glfw3 "https://github.com/glfw/glfw.git")
FetchContent_MakeAvailable(glfw3)

append_global_property(kryos_engine_include_dirs
        ${glfw_SOURCE_DIR}/include/
)
append_global_property(kryos_engine_libraries glfw)
