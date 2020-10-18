cmake_minimum_required(VERSION 3.15)

set(Dependencies Dependencies)

add_library(${Dependencies} INTERFACE)

target_link_libraries(${Dependencies} INTERFACE
        Catch2)