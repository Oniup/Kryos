cmake_minimum_required(VERSION 3.20)

set(include_dirs ${CMAKE_CURRENT_SOURCE_DIR}/include/)
file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR} "src/*.cpp")
file(GLOB_RECURSE headers ${CMAKE_CURRENT_SOURCE_DIR} "include/*.hpp")
append_global_property(kryos_engine_sources ${sources})
append_global_property(kryos_engine_sources ${headers})
append_global_property(kryos_engine_include_dirs ${include_dirs})
append_global_property(kryos_engine_compile_definitions RENDERER_USE_OPENGL_BACKEND)

add_subdirectory(thirdparty)
