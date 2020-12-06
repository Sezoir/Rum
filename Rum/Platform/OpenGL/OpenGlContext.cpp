#include "OpenGlContext.hpp"
// External libs
//#include <glad/glad.h>
// Project files
#include "Core/Log.hpp"

namespace Rum::Platform::OpenGL
{
    OpenGLContext::OpenGLContext(GLFWwindow* window)
        : mWindow(window)
    {
    }

    void OpenGLContext::init()
    {
        glfwMakeContextCurrent(mWindow);
        if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
            RUM_CORE_CRITICAL("GLAD failed to initialise.");
    }

    void OpenGLContext::swapBuffers()
    {
        glfwSwapBuffers(mWindow);
    }

} // namespace Rum::Platform::OpenGL