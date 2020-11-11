cmake_minimum_required(VERSION 3.15)

set(PLATFORM_FILES)

add_library(Platform)

# Add the correct platform/os specific files
if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    target_sources(Platform PUBLIC
            Windows/WindowsWindow.hpp
            Windows/WindowsWindow.cpp)
    target_include_directories(Platform PUBLIC
            ${PROJECT_SOURCE_DIR})
    target_compile_definitions(Platform PUBLIC
            -DRUM_PLATFORM_WINDOWS)
endif ()


target_compile_features(Platform PRIVATE
        cxx_std_17)

target_link_libraries(Platform PUBLIC
        Dependencies)