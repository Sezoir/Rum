#include "OpenGLContext.hpp"
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

        RUM_CORE_INFO("GLAD successfully initialised");
        RUM_CORE_INFO("OpenGL Info:");
        RUM_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
        RUM_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
        RUM_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
    }

    void OpenGLContext::swapBuffers()
    {
        glfwSwapBuffers(mWindow);
    }

    void OpenGLContext::setSwapInterval(uint8_t interval)
    {
        glfwSwapInterval(interval);
    }

} // namespace Rum::Platform::OpenGL