cmake_minimum_required(VERSION 3.20)
if (KRYOS_BUILD_TESTS )
    message("Kryos tests executable enabled for building")
    set(name "tests" CACHE INTERNAL "")
    project(${name})

    get_property(include_dirs GLOBAL PROPERTY kryos_engine_include_dirs)

    file(GLOB_RECURSE source_files ${CMAKE_CURRENT_SOURCE_DIR} "src/*.cpp")
    add_executable(${name} ${source_files})
    target_include_directories(${name}
        PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include
                ${include_dirs})
    target_link_libraries(${name} PUBLIC ${kryos_name})
endif()
