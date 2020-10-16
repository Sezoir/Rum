cmake_minimum_required(VERSION 3.15)

project(Engine)

add_library(${PROJECT_NAME} INTERFACE)

target_compile_features(${PROJECT_NAME} INTERFACE
        cxx_std_17)

add_subdirectory(Core)

target_link_libraries(${PROJECT_NAME} ${Dependencies} ${Core})