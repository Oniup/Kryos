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
file(GLOB_RECURSE KRYOS_CORE_HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/lib/*.h)
file(GLOB_RECURSE KRYOS_CORE_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/lib/*.c)

set(KRYOS_CORE_INCLUDE_DIRS 
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/kryos)

add_library(kryos-core STATIC
  ${KRYOS_CORE_HEADER_FILES}
  ${KRYOS_CORE_SOURCE_FILES})

target_include_directories(kryos-core PRIVATE
  ${KRYOS_CORE_INCLUDE_DIRS})

target_compile_definitions(kryos-core PUBLIC
  -D_CRT_SECURE_NO_WARNINGS)

# Editor Exec
# ----------------------------------------------------------------------------------------------------------------------

# file(GLOB_RECURSE KRYOS_ENGINE_HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/engine/*.h)
file(GLOB_RECURSE KRYOS_ENGINE_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/engine/*.c)

add_executable(kryos-engine ${KRYOS_ENGINE_SOURCE_FILES})

target_include_directories(kryos-engine PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/lib
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/kryos
  ${CMAKE_CURRENT_SOURCE_DIR}/engine)

target_compile_definitions(kryos-engine PUBLIC
  -D_CRT_SECURE_NO_WARNINGS)

target_link_libraries(kryos-engine PUBLIC
  kryos-core)
