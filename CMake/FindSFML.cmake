cmake_minimum_required(VERSION 3.15)

## Append the correct CMAKE_MODULE_PATH depending on the toolchain since we are using a precompiled library.
# Check if compiler is clang
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # Check if we are using GNU OR MSCV toolchain and append
    if (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "GNU" OR CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
        list(APPEND CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/SFML/Clang-MinGW-8.1.9)
    endif ()
endif ()

# Use static libs
set(SFML_STATIC_LIBRARIES TRUE)

# Get packages
find_package(SFML 2.5.1 CONFIG COMPONENTS system window graphics audio REQUIRED)