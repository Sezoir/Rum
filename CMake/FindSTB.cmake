cmake_minimum_required(VERSION 3.15)

add_library(stb INTERFACE)

target_include_directories(stb INTERFACE
        ${PROJECT_SOURCE_DIR}/STB/include)

target_compile_definitions(stb INTERFACE -DSTB_IMAGE_IMPLEMENTATION)
