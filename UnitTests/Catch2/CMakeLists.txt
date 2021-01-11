## Set minimum cmake
cmake_minimum_required(VERSION 3.15)

# Declare project
project(Catch2)

# Add library
add_library(Catch2 INTERFACE)

# Include directory
target_include_directories(Catch2 INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR})