cmake_minimum_required(VERSION 3.20)
project(kryos-engine CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

add_subdirectory(engine)

# Editor Exec
# ----------------------------------------------------------------------------------------------------------------------

# file(GLOB_RECURSE KRYOS_EDITOR_HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/editor/*.h)
file(GLOB_RECURSE KRYOS_EDITOR_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/editor/*.cpp)

add_executable(kryos-editor ${KRYOS_EDITOR_SOURCE_FILES})

target_include_directories(kryos-editor PRIVATE
  ${KRYOS_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/editor/src)

target_compile_definitions(kryos-editor PUBLIC
  -D_CRT_SECURE_NO_WARNINGS)

target_link_libraries(kryos-editor PUBLIC
  kryos)
