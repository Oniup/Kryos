cmake_minimum_required(VERSION 3.20)
project(KRYOS_ENGINE C)

# Options
# ----------------------------------------------------------------------------------------------------------------------
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED 11)

# Third party
# ----------------------------------------------------------------------------------------------------------------------

# Core Library
# ----------------------------------------------------------------------------------------------------------------------
file(GLOB_RECURSE KRYOS_HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)
file(GLOB_RECURSE KRYOS_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

set(KRYOS_INCLUDE_DIRS 
  ${CMAKE_CURRENT_SOURCE_DIR}/src/kryos)

add_library(kryos STATIC
  ${KRYOS_HEADER_FILES}
  ${KRYOS_SOURCE_FILES})

target_include_directories(kryos PRIVATE
  ${KRYOS_INCLUDE_DIRS})

target_compile_definitions(kryos PUBLIC
  -D_CRT_SECURE_NO_WARNINGS)

# Editor Exec
# ----------------------------------------------------------------------------------------------------------------------

# file(GLOB_RECURSE KRYOS_EDITOR_HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/editor/src/*.h)
file(GLOB_RECURSE KRYOS_EDITOR_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/editor/src/*.c)

add_executable(kryos-editor ${KRYOS_EDITOR_SOURCE_FILES})

target_include_directories(kryos-editor PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/src/kryos
  ${CMAKE_CURRENT_SOURCE_DIR}/editor/src)

target_compile_definitions(kryos-editor PUBLIC
  -D_CRT_SECURE_NO_WARNINGS)

target_link_libraries(kryos-editor PUBLIC
  kryos)
