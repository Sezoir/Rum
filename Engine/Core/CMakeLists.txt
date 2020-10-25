cmake_minimum_required(VERSION 3.15)

project(Core)

add_library(${PROJECT_NAME}
        Application.hpp
        Application.cpp
        )

target_compile_features(${PROJECT_NAME} PRIVATE
        cxx_std_17)

target_link_libraries(${PROJECT_NAME}
        Dependencies)