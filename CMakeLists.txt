# File        CMakeLists.txt
# Author      ZirconiumTian, GPT-6.2 Sol
# About       Builds the Ulang static library and optionally builds the
#             test executable.

cmake_minimum_required(VERSION 3.17)
project(Ulang LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(ulang STATIC src/lexer.cpp)
target_include_directories(ulang PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

option(ULANG_BUILD_TESTS "Build Ulang tests" OFF)
if(ULANG_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
