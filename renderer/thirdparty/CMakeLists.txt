add_library(
    glad STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/include/glad/glad.h
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/include/KHR/khrplatform.h
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glad/include/)

# file(GLOB_RECURSE NUKLEAR_SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/Nuklear/src/ "*.c")
# file(GLOB_RECURSE NUKLEAR_HEADER_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/Nuklear/src/ "*.h")
# add_library(
#     nuklear STATIC
#     ${NUKLEAR_SOURCE_FILES} ${NUKLEAR_HEADER_FILES})
# target_include_directories(nuklear PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Nuklear/src/)

set(kryos_gl_renderer_thirdparty_include_dirs
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/Nuklear/src/
    CACHE INTERNAL "")

append_global_property(kryos_engine_include_dirs ${kryos_gl_renderer_thirdparty_include_dirs})
append_global_property(kryos_engine_libraries glad)
