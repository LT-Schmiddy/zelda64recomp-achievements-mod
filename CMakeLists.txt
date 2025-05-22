cmake_minimum_required(VERSION 3.20)

project(recomp_achievements_lib)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(${TARGET_NAME} recomp_achievements_lib)

add_executable(${TARGET_NAME})

add_subdirectory("./src/extlib")
include_directories("./includes/extlib")

set_target_properties(${SHIM_TOOL_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "./arc/"
    LIBRARY_OUTPUT_DIRECTORY "./lib/"
    RUNTIME_OUTPUT_DIRECTORY "./bin/"
)
