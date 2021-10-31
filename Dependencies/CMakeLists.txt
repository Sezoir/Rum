cmake_minimum_required(VERSION 3.15)

project(Dependencies)

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

# Include SFML
#find_package(SFML MODULE)

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
        ${OPENGL_gl_LIBRARY} glad glfw Spdlog glm::glm stb EnTT::EnTT)


#target_link_libraries(${PROJECT_NAME} INTERFACE
#        sfml-system sfml-window sfml-graphics sfml-audio
#        Spdlog glm::glm)