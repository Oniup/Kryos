cmake_minimum_required(VERSION 3.20)
set(kryos_name "libkryos" CACHE INTERNAL "")
project(${kryos_name} VERSION 0.0.1 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED 11)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set_property(GLOBAL PROPERTY kryos_engine_sources "")
set_property(GLOBAL PROPERTY kryos_engine_include_dirs "")
set_property(GLOBAL PROPERTY kryos_engine_libraries "")
set_property(GLOBAL PROPERTY kryos_engine_compile_definitions "")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(KRYOS_BUILD_EDITOR "Build kryos-engine editor executable" ON)
option(KRYOS_BUILD_TESTS "Build all kryos-engine library tests" ON)
option(KRYOS_BUILD_SHARED_LIBRARY "Build kryos-engine core as a shared library" OFF)
option(KRYOS_SHOW_CORE_LIBRARY_SOURCES "On cmake reload, print all sources that build up kryos-engine core" OFF)

set(KRYOS_UNIVERSAL_COMPILE_DEFINITIONS
    PUBLIC  _CRT_SECURE_NO_WARNINGS
            CACHE INTERNAL "")

if (KRYOS_BUILD_SHARED_LIBRARY)
    message("Kryos core enabled for building as a SHARED library")
    set(kryos_library_type SHARED)
    set(KRYOS_UNIVERSAL_COMPILE_DEFINITIONS
        "${KRYOS_UNIVERSAL_COMPILE_DEFINITIONS} KRYOS_BUILD_SHARED")
else()
    message("Kryos core enabled for building as a STATIC library")
    set(kryos_library_type STATIC)
endif ()

function(append_global_property property)
    get_property(tmp GLOBAL PROPERTY ${property})
    foreach (arg ${ARGN})
        set(tmp ${tmp} ${arg})
    endforeach()
    set_property(GLOBAL PROPERTY ${property} ${tmp})
endfunction()

set(engine_modules tools core renderer CACHE INTERNAL "")
foreach (module ${engine_modules})
    add_subdirectory(${module})
endforeach()

get_property(source_files GLOBAL PROPERTY kryos_engine_sources)
get_property(include_dirs GLOBAL PROPERTY kryos_engine_include_dirs)
get_property(libraries GLOBAL PROPERTY kryos_engine_libraries)
get_property(compile_definitions GLOBAL PROPERTY kryos_engine_compile_definitions)

if (KRYOS_SHOW_CORE_LIBRARY_SOURCES)
    function(print_sources title)
        message(${title})
        foreach (item ${ARGN})
            message(" + ${item}")
        endforeach()
    endfunction()
    print_sources("\nKryos Core Library Sources:" ${source_files})
    print_sources("\nKryos Core Library Include_dirs:" ${include_dirs})
    print_sources("\nKryos Core Library Libraries:" ${libraries})
    print_sources("\nKryos Core Library Compile Definitions:" ${compile_definitions})
endif ()

add_library(${kryos_name} ${kryos_library_type} ${source_files})
target_include_directories(${kryos_name} PUBLIC ${include_dirs})
target_link_libraries(${kryos_name} PUBLIC ${libraries})
target_compile_definitions(${kryos_name} PUBLIC ${compile_definitions})

add_subdirectory(editor)
add_subdirectory(tests)
