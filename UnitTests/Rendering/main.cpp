#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

#include <Rum.hpp>
#include <Renderer/Renderer.hpp>
#include <Renderer/RendererApi.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main(int argc, char* argv[])
{
    // Setup GLFW/OpenGL
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(800, 800, "BufferTests", NULL, NULL);
    glfwMakeContextCurrent(window);
    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        RUM_CORE_CRITICAL("GLAD failed to initialise.");

    // Initialise logger
    Rum::Core::Log::init();

    // Setup renderer
    Rum::Renderer::Renderer renderer;
    renderer.setDrawAPI(Rum::Renderer::DrawAPI::OpenGL);

    // Run the tests
    int result = Catch::Session().run(argc, argv);

    return result;
}