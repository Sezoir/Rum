cmake_minimum_required(VERSION 3.15)

project(ROOT)

option(ENABLE_ASSERTS "Enable assert checks" ON)
option(ENABLE_TESTS "Build unit tests" ON)
option(ENABLE_EXAMPLES "Build examples" ON)

if (ENABLE_TESTS STREQUAL ON)
    enable_testing()
endif ()

add_subdirectory(Dependencies)

add_subdirectory(Rum)

add_subdirectory(Examples)

add_subdirectory(UnitTests)