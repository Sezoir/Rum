cmake_minimum_required(VERSION 3.15)

set(PLATFORM_FILES)

add_library(Renderer
        Renderer.hpp
        Renderer.cpp
        RendererAPI.hpp
        RendererApi.cpp
        DrawContext.hpp
        DrawContext.cpp
        Buffers.hpp
        Buffers.cpp
        VertexArray.hpp
        VertexArray.cpp
        Shader.hpp
        Shader.cpp
        Texture.hpp
        Texture.cpp)

target_include_directories(Renderer PUBLIC
        ${PROJECT_SOURCE_DIR})

target_compile_features(Renderer PRIVATE
        cxx_std_17)

target_compile_definitions(Renderer PUBLIC
        -DGLFW_INCLUDE_NONE)

target_link_libraries(Renderer PUBLIC
        Dependencies Platform)