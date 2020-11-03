cmake_minimum_required(VERSION 3.15)

# Create library
add_library(Spdlog INTERFACE)

## Append the correct CMAKE_MODULE_PATH depending on the toolchain since we are using a precompiled library.
# Check if compiler is clang
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # Check if we are using MSCV toolchain and enable exceptions (they are disabled by default)
    if (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
        target_compile_options(Spdlog INTERFACE "/GX")
    endif ()
endif ()

# Add header files
target_include_directories(Spdlog INTERFACE
        ${PROJECT_SOURCE_DIR}/Spdlog/include)