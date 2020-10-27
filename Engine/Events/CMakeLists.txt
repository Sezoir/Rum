cmake_minimum_required(VERSION 3.15)

project(Events)

add_library(${PROJECT_NAME} INTERFACE
        )

target_compile_features(${PROJECT_NAME} INTERFACE
        cxx_std_17)

target_include_directories(${PROJECT_NAME} INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} INTERFACE
        Dependencies)