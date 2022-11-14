cmake_minimum_required(VERSION 3.15)

add_library(Scene
        Scene.hpp
        Scene.cpp
        Entity.hpp
        Entity.cpp
        Components.hpp
        SceneManager.hpp
        SceneManager.cpp)

target_include_directories(Scene PUBLIC
        ${PROJECT_SOURCE_DIR})

target_compile_features(Scene PRIVATE
        cxx_std_17)

target_link_libraries(Scene PUBLIC
        Dependencies Renderer)