cmake_minimum_required(VERSION 3.15)

add_library(Core
        Application.hpp
        Application.cpp
        Window.hpp
        Window.cpp
        Log.hpp
        Log.cpp
        )

target_compile_features(Core PRIVATE
        cxx_std_17)

target_include_directories(Core PUBLIC
        ${PROJECT_SOURCE_DIR})

target_link_libraries(Core PUBLIC
        Dependencies Platform)