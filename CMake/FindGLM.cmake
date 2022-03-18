cmake_minimum_required(VERSION 3.15)

set(DEP_GLM_VERSION "0.9.9.9")

list(APPEND CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/glm/glm-${DEP_GLM_VERSION}/cmake)

# Get packages
find_package(glm CONFIG)
