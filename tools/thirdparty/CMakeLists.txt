cmake_minimum_required(VERSION 3.20)
include(FetchContent)

fetch_dependency(glm https://github.com/g-truc/glm.git)
FetchContent_MakeAvailable(glm)

set(include_dirs
    PRIVATE
        ${glm_SOURCE_DIR}/
)

append_global_property(kryos_engine_include_dirs ${include_dirs})
append_global_property(kryos_engine_libraries glm)
