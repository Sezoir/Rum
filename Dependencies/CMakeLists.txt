cmake_minimum_required(VERSION 3.15)

project(Dependencies)

## Options handling
set(RUM_AVALIABLE_BUILD_LIBS_OPTIONS STATIC PREBUILD LOCAL)
set_property(CACHE RUM_BUILD_LIBS_METHOD PROPERTY STRINGS ${RUM_AVALIABLE_BUILD_LIBS_OPTIONS})
if(NOT RUM_BUILD_LIBS_METHOD IN_LIST RUM_AVALIABLE_BUILD_LIBS_OPTIONS)
    message(FATAL_ERROR "RUM_BUILD_LIBS_METHOD=${RUM_BUILD_LIBS_METHOD} build option must be one of: ${RUM_AVALIABLE_BUILD_LIBS_OPTIONS}")
endif()

if (${RUM_BUILD_LIBS_METHOD} STREQUAL "LOCAL")
    message(FATAL_ERROR "BUILD_LIBS_METHOD=LOCAL is not yet supported.")
endif()

## Dependency handling
add_library(${PROJECT_NAME} INTERFACE)

# Set project find cmakes folder
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

# Include OpenGL
find_package(OpenGL REQUIRED)
target_include_directories(Dependencies INTERFACE ${OPENGL_INCLUDE_DIR})

# Include glad
find_package(GLAD MODULE)

# Include spdlog
find_package(Spdlog MODULE)

# Include glfw
find_package(GLFW MODULE)

# Include glm
find_package(GLM MODULE)

# Include stb
find_package(STB MODULE)

# Include entt
find_package(EnTT MODULE)

# Link all libraries
target_link_libraries(${PROJECT_NAME} INTERFACE
        ${OPENGL_gl_LIBRARY} glad glfw spdlog glm::glm stb EnTT::EnTT)
