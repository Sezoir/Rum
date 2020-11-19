cmake_minimum_required(VERSION 3.15)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    list(APPEND CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/GLFW/MinGW-x86_64-8.1.0/${CMAKE_BUILD_TYPE}/lib/cmake/glfw3)
endif ()

#if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
#    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
#        list(APPEND CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/GLFW/MinGW-x86_64-8.1.0/Debug/lib/cmake/glfw3)
#    elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
#        list(APPEND CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/GLFW/MinGW-x86_64-8.1.0/Release/lib/cmake/glfw3)
#    endif ()
#endif ()

# Get packages
find_package(glfw3 CONFIG REQUIRED)