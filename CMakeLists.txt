cmake_minimum_required(VERSION 3.15)

project(ROOT)

enable_testing()

set(ENABLE_EXAMPLES ON)

add_subdirectory(Dependencies)

add_subdirectory(Rum)

add_subdirectory(Examples)

add_subdirectory(UnitTests)