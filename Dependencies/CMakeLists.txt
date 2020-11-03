cmake_minimum_required(VERSION 3.15)

project(Dependencies)

add_library(${PROJECT_NAME} INTERFACE)

# Set project find cmakes folder
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

# Include spdlog
find_package(Spdlog MODULE)

# Include SFML
find_package(SFML MODULE)

# Link all libraries
target_link_libraries(${PROJECT_NAME} INTERFACE
        sfml-system sfml-window sfml-graphics sfml-audio
        Spdlog)