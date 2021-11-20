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
function(add_unit_test FOLDER)
    # Set target name
    set(TARGET ${FOLDER}_Unit_Test)

    # Get all source files
    file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS ${FOLDER}/*.cpp ${FOLDER}/*.c)

    # Add executable
    add_executable(${TARGET}
            ${SOURCE_FILES}
            )
    # Set c++ standard
    target_compile_features(${TARGET} INTERFACE cxx_std_17)

    # Add catch2
    target_include_directories(${TARGET} PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/Catch2)

    # Pass flag for big source files for GNU (due to many SECTIONS resulting in assembler errors)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(${TARGET} PUBLIC "-Wa,-mbig-obj")
    endif ()

    # Link libraries
    target_link_libraries(${TARGET}
            Rum
            )

    add_test(NAME ${TARGET} COMMAND ${FOLDER})

endfunction()

if (ENABLE_UNIT_TESTS)
    # Declare project
    project(UnitTests C CXX)

    # Add Tests
    add_unit_test(Core)
    add_unit_test(Window)
    add_unit_test(Input)
    add_unit_test(Rendering)

    configure_file(Rendering/shader.vert shader.vert COPYONLY)
    configure_file(Rendering/shader.frag shader.frag COPYONLY)

endif (ENABLE_UNIT_TESTS)
