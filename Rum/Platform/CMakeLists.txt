cmake_minimum_required(VERSION 3.15)

add_library(Platform
        OpenGL/OpenGLContext.hpp
        OpenGL/OpenGLContext.cpp
        OpenGL/OpenGLRendererApi.hpp
        OpenGL/OpenGLRendererApi.cpp
        OpenGL/OpenGLUtilities.hpp
        OpenGL/OpenGLUtilities.cpp
        OpenGL/OpenGLBuffers.hpp
        OpenGL/OpenGLBuffers.cpp
        OpenGL/OpenGLVertexArray.hpp
        OpenGL/OpenGLVertexArray.cpp
        OpenGL/OpenGLShader.hpp
        OpenGL/OpenGLShader.cpp
        OpenGL/OpenGLTexture2D.hpp
        OpenGL/OpenGLTexture2D.cpp
        GLFW/Utility.hpp
        GLFW/Utility.cpp)

# Add the correct platform/os specific files
if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    target_sources(Platform PUBLIC
            Windows/WindowsWindow.hpp
            Windows/WindowsWindow.cpp)
    target_include_directories(Platform PUBLIC
            ${PROJECT_SOURCE_DIR})
    target_compile_definitions(Platform PUBLIC
            -DRUM_PLATFORM_WINDOWS)
endif ()


target_compile_features(Platform PRIVATE
        cxx_std_17)

target_link_libraries(Platform PUBLIC
        Dependencies)