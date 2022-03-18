cmake_minimum_required(VERSION 3.15)

set(DEP_SPDLOG_VERSION "1.8.1")

# Create library
add_library(spdlog INTERFACE)

## Append the correct CMAKE_MODULE_PATH depending on the toolchain since we are using a precompiled library.
# Check if compiler is clang
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # Check if we are using MSCV toolchain and enable exceptions (they are disabled by default)
    if (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
        target_compile_options(spdlog INTERFACE "/GX")
    endif ()
endif ()

# Add header files
target_include_directories(spdlog INTERFACE
        ${PROJECT_SOURCE_DIR}/spdlog/spdlog-${DEP_SPDLOG_VERSION}/include)
