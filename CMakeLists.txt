# Project CMake List File

cmake_minimum_required(VERSION 4.0.2)
project(
    "Simple CLI" 
    VERSION 0.0.0
    DESCRIPTION "A simple command line interface tool for C++ projects."
    LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_INCLUDES OFF)

set(ROOT_DIR ${CMAKE_SOURCE_DIR})
set(SIMPLE_CLI "${ROOT_DIR}/simpleCLI")
set(EXAMPLE "${ROOT_DIR}/example")
set(SOURCE "source")
set(HEADER "header")
set(TEST "test")
set(BUILD "build")
set(BINARY "binary")
set(LIBRARY "library")

add_subdirectory(${SIMPLE_CLI})
add_subdirectory(${EXAMPLE})