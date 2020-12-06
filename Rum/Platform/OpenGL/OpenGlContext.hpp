#pragma once
// External libs
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// Project files
#include "Renderer/DrawContext.hpp"

namespace Rum::Platform::OpenGL
{
    class OpenGLContext : public Renderer::DrawContext
    {
    public:
        OpenGLContext(GLFWwindow* window);

        void init() override;
        void swapBuffers() override;

    private:
        GLFWwindow* mWindow = nullptr;
    };
} // namespace Rum::Platform::OpenGL
