## Set minimum cmake
cmake_minimum_required(VERSION 3.15)

#########################################################
# Options
#########################################################
OPTION(ENABLE_UNIT_TESTS "Enables all unit tests." ON)


#########################################################
# Unit tests
#########################################################
# Add each folder for testing
function(add_folder FOLDER)
    # Get all source files
    file(GLOB_RECURSE GLOB_RESULT CONFIGURE_DEPENDS ${FOLDER}/*.c ${FOLDER}/*.cpp)
    # Append source files
    set(SOURCE_FILES ${SOURCE_FILES} ${GLOB_RESULT} PARENT_SCOPE)
endfunction()

if (ENABLE_UNIT_TESTS)
    # Declare project
    project(UnitTests C CXX)

    # Add Tests
    add_folder(Window)
    add_folder(Input)

    # Add executable
    add_executable(${PROJECT_NAME}
            main.cpp
            ${SOURCE_FILES}
            )

    # Set c++ standard
    target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)

    # Add catch2
    target_include_directories(${PROJECT_NAME} PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/Catch2)

    # Pass flag for big source files for GNU (due to many SECTIONS resulting in assembler errors)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(${PROJECT_NAME} PUBLIC "-Wa,-mbig-obj")
    endif ()

    # Link libraries
    target_link_libraries(${PROJECT_NAME}
            Rum
            )
endif (ENABLE_UNIT_TESTS)
