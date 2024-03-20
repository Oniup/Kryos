cmake_minimum_required(VERSION 3.20)
set(kryos_name "kryos" CACHE INTERNAL "")
set(kryos_version "0.0.1")
project(${kryos_name})

function(append_global_property property)
    get_property(tmp GLOBAL PROPERTY ${property})
    foreach (arg ${ARGN})
        set(tmp ${tmp} ${arg})
    endforeach()
    set_property(GLOBAL PROPERTY ${property} ${tmp})
endfunction()

function(fetch_content name git_https)
    FetchContent_Declare(${name}
        GIT_REPOSITORY ${git_https}
        GIT_TAG master
    )
endfunction()

function(fetch_dependency name git_https)
    find_package(${name} QUIET)
    if (NOT "${name}_FOUND")
        message("${name} package not installed, installing dependency from ${git_https}...")
        fetch_content(${name} ${git_https})
    endif()
endfunction()

option(KRYOS_BUILD_EDITOR "Build kryos-engine editor executable" ON)
option(KRYOS_BUILD_TESTS "Build all kryos-engine library tests" ON)
option(KRYOS_BUILD_SHARED_LIBRARY "Build kryos-engine core as a shared library" ON)
option(KRYOS_SHOW_CORE_LIBRARY_SOURCES "On cmake reload, print all sources that build up kryos-engine core" OFF)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED 23)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY kryos_engine_sources "")
set_property(GLOBAL PROPERTY kryos_engine_include_dirs "")
set_property(GLOBAL PROPERTY kryos_engine_libraries "")
set_property(GLOBAL PROPERTY kryos_engine_compile_definitions _CRT_SECURE_NO_WARNINGS)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    set_property(GLOBAL PROPERTY kryos_engine_compile_options -Wall -Wextra)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    set_property(GLOBAL PROPERTY kryos_engine_compile_options /EHsc /MTd /W2 /c)
endif()

if (KRYOS_BUILD_SHARED_LIBRARY)
    message("Kryos core enabled for building as a SHARED library")
    append_global_property(kryos_engine_compile_options -fPIC)
    set(kryos_library_type SHARED CACHE INTERNAL "")
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    if (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
        append_global_property(kryos_engine_compile_options "KRYOS_WIN_EXPORT")
    endif()
else()
    message("Kryos core enabled for building as a STATIC library")
    set(kryos_library_type STATIC )
endif ()

set(engine_modules tools core renderer)
foreach (module ${engine_modules})
    add_subdirectory(${module})
endforeach()

get_property(source_files GLOBAL PROPERTY kryos_engine_sources)
get_property(include_dirs GLOBAL PROPERTY kryos_engine_include_dirs)
get_property(libraries GLOBAL PROPERTY kryos_engine_libraries)
get_property(compile_definitions GLOBAL PROPERTY kryos_engine_compile_definitions)
get_property(compile_options GLOBAL PROPERTY kryos_engine_compile_options)

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
endif()

add_library(${kryos_name} ${kryos_library_type} ${source_files})
target_include_directories(${kryos_name} PUBLIC ${include_dirs})
target_link_libraries(${kryos_name} PUBLIC ${libraries})
target_compile_definitions(${kryos_name} PUBLIC ${compile_definitions})
target_compile_options(${kryos_name} PRIVATE  ${compile_options})
set_target_properties(${kryos_name}
    PROPERTIES
        VERSION ${kryos_version}
        SOVERSION ${kryos_version}
)

add_subdirectory(editor)
add_subdirectory(tests)
