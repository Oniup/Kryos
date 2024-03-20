add_library(
    glad ${kryos_library_type}
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/include/glad/glad.h
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/include/KHR/khrplatform.h
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glad/include/)

set(include_dirs
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/include/
)

append_global_property(kryos_engine_include_dirs ${include_dirs})
append_global_property(kryos_engine_libraries glad)
