# Project CMake List File

cmake_minimum_required(VERSION 4.0.2)
project(
    "Simple CLI" 
    VERSION 1.0.0
    DESCRIPTION "A simple command line interface tool for C++ projects."
    LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Export compile commands for tools like clangd
set(CMAKE_CXX_SCAN_FOR_MODULES OFF) # No module support yet

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(
        -Wno-inline-namespace-reopened-noninline
        -Wno-backslash-newline-escape
    )
endif()

set(ROOT_DIR ${CMAKE_SOURCE_DIR})
set(SIMPLE_CLI "${ROOT_DIR}/simpleCLI")
set(EXAMPLE "${ROOT_DIR}/example")
set(SOURCE "SOURCE")
set(HEADER "HEADER")
set(TEST "test")
set(BUILD "build")
set(BINARY "binary")
set(LIBRARY "library")

add_subdirectory(${SIMPLE_CLI})
add_subdirectory(${EXAMPLE})
