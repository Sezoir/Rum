cmake_minimum_required(VERSION 3.15)

set(DEP_GLFW_VERSION "3.3.7")
set(DEP_GLFW_BUILD_DIR "${PROJECT_SOURCE_DIR}/glfw/build/${CMAKE_BUILD_TYPE}---${CMAKE_CXX_COMPILER_ID}")
set(DEP_GLFW_BUILD_LIB_DIR "${DEP_GLFW_BUILD_DIR}/src")
set(DEP_GLFW_SOURCE_DIR "${PROJECT_SOURCE_DIR}/glfw/glfw-${DEP_GLFW_VERSION}")
set(DEP_GLFW_BUILD_ARGS "-DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF")

if (${CMAKE_GENERATOR} MATCHES "Visual Studio")
    set(DEP_GLFW_BUILD_LIB_DIR "${DEP_GLFW_BUILD_LIB_DIR}/${CMAKE_BUILD_TYPE}")
endif ()

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
    set(DEP_GLFW_BUILD_FILE "glfw3")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(DEP_GLFW_BUILD_FILE "libglfw3")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL " GNU")
    set(DEP_GLFW_BUILD_FILE "glfw3")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(DEP_GLFW_BUILD_FILE "glfw3")
endif ()

if (RUM_BUILD_LIBS_METHOD STREQUAL PREBUILD)
    execute_process(COMMAND cmake -DCMAKE_MAKE_PROGRAM=${CMAKE_MAKE_PROGRAM} -G ${CMAKE_GENERATOR} -B ${DEP_GLFW_BUILD_DIR} -S ${DEP_GLFW_SOURCE_DIR} ${DEP_GLFW_BUILD_ARGS})

    add_custom_target(glfwBuild COMMAND cmake --build ${DEP_GLFW_BUILD_DIR} BYPRODUCTS ${DEP_GLFW_BUILD_LIB_DIR}/${DEP_GLFW_BUILD_FILE}.${RUM_DEPENDENCY_EXTENSION})

    add_library(glfw STATIC IMPORTED)
    set_target_properties(glfw PROPERTIES
            IMPORTED_GLOBAL true
            IMPORTED_LOCATION "${DEP_GLFW_BUILD_LIB_DIR}/${DEP_GLFW_BUILD_FILE}.${RUM_DEPENDENCY_EXTENSION}"
            INTERFACE_INCLUDE_DIRECTORIES "${DEP_GLFW_SOURCE_DIR}/include"
            )

    add_dependencies(glfw glfwBuild)

elseif (RUM_BUILD_LIBS_METHOD STREQUAL STATIC)
    add_subdirectory(${DEP_GLFW_SOURCE_DIR})
endif ()
