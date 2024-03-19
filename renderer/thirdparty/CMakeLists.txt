add_library(
    glad STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/include/glad/glad.h
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/include/KHR/khrplatform.h
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glad/include/)

set(kryos_gl_renderer_thirdparty_include_dirs
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/Nuklear/src/
    CACHE INTERNAL "")

append_global_property(kryos_engine_include_dirs ${kryos_gl_renderer_thirdparty_include_dirs})
append_global_property(kryos_engine_libraries glad)
