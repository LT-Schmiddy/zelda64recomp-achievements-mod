cmake_minimum_required(VERSION 3.20)

project(recomp_achievements_lib)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TARGET_NAME AchievementNative)

include_directories("./offline_build")
include_directories("./include/extlib")
include_directories("./include/shared")
include_directories("./src/extlib")

add_library(${TARGET_NAME} SHARED)

add_subdirectory("./src/extlib")

set_target_properties(${TARGET_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "./arc/"
    LIBRARY_OUTPUT_DIRECTORY "./lib/"
    RUNTIME_OUTPUT_DIRECTORY "./bin/"
)
