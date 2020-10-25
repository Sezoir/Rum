cmake_minimum_required(VERSION 3.15)

project(Dependencies)

add_library(${PROJECT_NAME} INTERFACE)

# Include SFML
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/SFML)
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)
target_include_directories(${PROJECT_NAME} INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/SFML/include)

# Link all libraries
target_link_libraries(${PROJECT_NAME} INTERFACE
        sfml-system sfml-window sfml-graphics sfml-audio)