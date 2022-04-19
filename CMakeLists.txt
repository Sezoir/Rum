cmake_minimum_required(VERSION 3.15)

project(ROOT)

option(ENABLE_ASSERTS "Enable assert checks" ON)
option(ENABLE_TESTS "Build unit tests" ON)
option(ENABLE_EXAMPLES "Build examples" ON)

# Choose the method for building the dependencies. Note that this only applies to specific
# dependencies where it would make sense. Available options are the following:
#   STATIC: All the dependencies are built at compile time
#   PREBUILD: Build all the dependencies at compile time in a separate build directory.
#             Subsequent cleans will not affect these build directories, meaning the user
#             only has to build these libraries once. This should result in quicker compile times.
#             This is mainly aimed at developers of this library.
#   LOCAL:    Use existing builds of the dependencies on the developers local machine. This option
#             requires passing cmake the paths to the existing build directories when generating.
#             The corresponding 'FindXXX.cmake' should contain the appropriate variable that needs to
#             be set. (** Note that this option has not yet been implemented **)
set(RUM_BUILD_LIBS_METHOD STATIC CACHE STRING "Select the build method for the dependencies.")

if (ENABLE_TESTS STREQUAL ON)
    enable_testing()
endif ()

# Set project cmake folder
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR})
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

find_package(Platform)

add_subdirectory(Dependencies)

add_subdirectory(Rum)

add_subdirectory(Examples)

add_subdirectory(UnitTests)