// Std libs
#include <memory>
// Rum files
#include <Rum.hpp>
#include <Renderer/Buffers.hpp>
#include <Renderer/VertexArray.hpp>
#include <Platform/OpenGL/OpenGLBuffers.hpp>
#include <Platform/OpenGL/OpenGLVertexArray.hpp>
// External libs
#include <catch.hpp>
#include <GLFW/glfw3.h>

using namespace Rum::Renderer;
using namespace Rum::Platform::OpenGL;

TEST_CASE("Testing Buffers", "[Renderer][Buffer]")
{
    SECTION("ElementLayer")
    {
        Element one(ShaderDataType::Float, 3, 0);
        Element two(ShaderDataType::Float3, 1, 0);
        Element three(ShaderDataType::Float2, 2, 0);
        Element four(ShaderDataType::Int, 3, 0);
        ElementLayout layout({one, two, three, four});

        // Check actually memory size in bytes
        REQUIRE(layout.getBufferSize() == 52);
        // Check individual element count size
        REQUIRE(layout.getStride() == 9);
        // Check offset are correctly set
        REQUIRE(layout.getElements()[1].mOffset == 3);
    }

    // Setup GLFW/OpenGL
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(800, 800, "BufferTests", NULL, NULL);
    glfwMakeContextCurrent(window);
    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        RUM_CORE_CRITICAL("GLAD failed to initialise.");

    // Setup renderer
    Renderer renderer;
    renderer.setDrawAPI(DrawAPI::OpenGL);

    SECTION("OpenGLVertexBuffer")
    {
        SECTION("Vector Creation test")
        {
            std::vector<float> vertices = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};
            std::shared_ptr<VertexBuffer> vbo = VertexBuffer::create(*vertices.data());
            auto openGLVbo = std::static_pointer_cast<OpenGLVertexBuffer>(vbo);

            openGLVbo->bind();
            openGLVbo->unbind();
            std::vector<float> subVertices = {0.1, -0.5, 0.5};
            openGLVbo->setData(*subVertices.data());
        }
        SECTION("Array Creation test")
        {
            std::array<float, 9> vertices = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};
            std::shared_ptr<VertexBuffer> vbo = VertexBuffer::create(*vertices.data());
            auto openGLVbo = std::static_pointer_cast<OpenGLVertexBuffer>(vbo);

            openGLVbo->bind();
            openGLVbo->unbind();
            std::array<float, 3> subVertices = {0.1, -0.5, 0.5};
            openGLVbo->setData(*subVertices.data());
        }
        SECTION("Float-array creation test")
        {
            float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};
            std::shared_ptr<VertexBuffer> vbo = VertexBuffer::create(*vertices);
            auto openGLVbo = std::static_pointer_cast<OpenGLVertexBuffer>(vbo);

            openGLVbo->bind();
            openGLVbo->unbind();
            float subVertices[] = {0.1, -0.5, 0.5};
            openGLVbo->setData(*subVertices);
        }
    }

    SECTION("OpenGLIndexBuffer")
    {
        uint64_t indices[] = {0, 1, 3, 1, 2, 3};
        auto ibo = IndexBuffer::create(*indices);
        auto openGLIbo = std::unique_ptr<OpenGLIndexBuffer>(static_cast<OpenGLIndexBuffer*>(ibo.release()));
        openGLIbo->bind();
        openGLIbo->unbind();
    }

    SECTION("OpenGLVertexArray")
    {
        Element one(ShaderDataType::Float, 3, 0);
        ElementLayout layout({one});

        constexpr float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};
        std::shared_ptr<VertexBuffer> vbo = VertexBuffer::create(*vertices);
        vbo->setLayout(layout);

        uint64_t indices[] = {0, 1, 3, 1, 2, 3};
        auto ibo = IndexBuffer::create(*indices);

        std::unique_ptr<VertexArray> vao = VertexArray::create();
        auto openGLVao = std::unique_ptr<OpenGLVertexArray>(static_cast<OpenGLVertexArray*>(vao.release()));
        openGLVao->addVertexObject(vbo);
        openGLVao->setIndexBuffer(ibo);

        openGLVao->bind();
        openGLVao->unbind();
    }
}