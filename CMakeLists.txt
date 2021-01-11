cmake_minimum_required(VERSION 3.15)

project(ROOT)

enable_testing()

add_subdirectory(Dependencies)

add_subdirectory(Rum)

add_subdirectory(UnitTests)