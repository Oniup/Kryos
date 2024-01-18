cmake_minimum_required(VERSION 3.20)
project(Kryos CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

# Library
# ----------------------------------------------------------------------------------------------------------------------
file(GLOB_RECURSE KRYOS_HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE KRYOS_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

set(KRYOS_INCLUDE_DIRS
  ${CMAKE_CURRENT_SOURCE_DIR}
  CACHE INTERNAL "")

add_library(Kryos STATIC
  ${KRYOS_HEADER_FILES}
  ${KRYOS_SOURCE_FILES})

target_include_directories(Kryos PRIVATE
  ${KRYOS_INCLUDE_DIRS})

target_compile_definitions(Kryos PUBLIC -D_CRT_SECURE_NO_WARNINGS)
