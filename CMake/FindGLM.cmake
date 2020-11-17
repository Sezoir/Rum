cmake_minimum_required(VERSION 3.15)

list(APPEND CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/GLM/cmake)

# Get packages
find_package(glm CONFIG)