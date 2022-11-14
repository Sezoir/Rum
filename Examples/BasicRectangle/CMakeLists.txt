## Set minimum cmake
cmake_minimum_required(VERSION 3.15)

project(BasicRectangle)

# Get all source files
#file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS *.cpp *.c)

# Add executable
add_executable(${PROJECT_NAME}
        main.cpp
        )
# Set c++ standard
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)

# Add catch2
target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR})

# Pass flag for big source files for GNU (due to many SECTIONS resulting in assembler errors)
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${PROJECT_NAME} PUBLIC "-Wa,-mbig-obj")
endif ()

# Link libraries
target_link_libraries(${PROJECT_NAME}
        Rum
        )

configure_file(shader.vert shader.vert COPYONLY)
configure_file(shader.frag shader.frag COPYONLY)
configure_file(texture.jpg texture.jpg COPYONLY)