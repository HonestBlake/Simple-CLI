cmake_minimum_required(VERSION 4.0.2)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(
    "Simple CLI"
    VERSION 1.0.0
    DESCRIPTION "A simple command line interface tool for C++ projects."
    LANGUAGES CXX
)

option(SIMPLE_CLI_USE_MODULES "Build Simple CLI with C++ module interfaces instead of legacy headers." OFF)
option(BUILD_EXAMPLE "Build the Simple CLI example executable." OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ${SIMPLE_CLI_USE_MODULES})

message(STATUS "Selected C++ Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Simple CLI Uses Modules: ${SIMPLE_CLI_USE_MODULES}")
message(STATUS "Building Example: ${BUILD_EXAMPLE}")

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(
        -Wno-backslash-newline-escape
    )
endif()

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(INCLUDE "${ROOT_DIR}/include")
set(SIMPLE_CLI "${ROOT_DIR}/simpleCli")
set(EXAMPLE "${ROOT_DIR}/example")

add_subdirectory(${SIMPLE_CLI})

if(BUILD_EXAMPLE)
    add_subdirectory(${EXAMPLE})
endif()
