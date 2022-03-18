cmake_minimum_required(VERSION 3.15)

add_library(glad
        ${PROJECT_SOURCE_DIR}/GLAD/src/glad.c)

target_include_directories(glad PUBLIC
        ${PROJECT_SOURCE_DIR}/GLAD/include)
