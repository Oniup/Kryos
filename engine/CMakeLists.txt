cmake_minimum_required(VERSION 3.20)
project(libkryos CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED 11)

# Library
# ----------------------------------------------------------------------------------------------------------------------
file(GLOB_RECURSE KRYOS_HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE KRYOS_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

set(KRYOS_INCLUDE_DIRS
  ${CMAKE_CURRENT_SOURCE_DIR}
  CACHE INTERNAL "")

add_library(kryos STATIC
  ${KRYOS_HEADER_FILES}
  ${KRYOS_SOURCE_FILES})

target_include_directories(kryos PRIVATE
  ${KRYOS_INCLUDE_DIRS})

target_compile_definitions(kryos PUBLIC
  -D_CRT_SECURE_NO_WARNINGS)
