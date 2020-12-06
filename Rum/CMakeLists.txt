cmake_minimum_required(VERSION 3.15)

project(Rum)

add_library(${PROJECT_NAME} INTERFACE)

target_compile_features(${PROJECT_NAME} INTERFACE
        cxx_std_17)

add_subdirectory(Platform)
add_subdirectory(Renderer)
add_subdirectory(Core)

target_include_directories(${PROJECT_NAME} INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} INTERFACE
        Core)