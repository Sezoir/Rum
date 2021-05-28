#include <Rum.hpp>
#include <memory>

int main()
{
    using namespace Rum::Core;
    using namespace Rum::Renderer;

    Application app;

    auto shader = Shader::create("triangle", "shader.vert", "shader.frag");
    shader->compile();

    float vertices[] = {0.5f,  0.5f,  0.0f, // top right
                        0.5f,  -0.5f, 0.0f, // bottom right
                        -0.5f, -0.5f, 0.0f, // bottom left
                        -0.5f, 0.5f,  0.0f, // top left
                        0.0f,  0.8f,  0.0f};
    uint32_t indices[] = {
        0, 1, 3, // first Triangle
        4, 2, 3  // second Triangle
    };

    auto vertexArray = VertexArray::create();
    vertexArray->bind();

    auto vertexBuffer = VertexBuffer::create(vertices, sizeof(vertices), BufferMemoryType::STATIC_DRAW);
    ElementLayout layout = {{ShaderDataType::Float3, "position"}};
    vertexBuffer->setLayout(layout);
    vertexBuffer->bind();

    auto indicesBuffer =
        IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t), BufferMemoryType::STATIC_DRAW);
    indicesBuffer->bind();

    vertexArray->addVertexObject(vertexBuffer);
    vertexArray->setIndexBuffer(std::move(indicesBuffer));

    vertexArray->unbind();

    auto& window = app.getWindow();

    while(window.isOpen())
    {
        window.pollInput();

        Renderer::getAPI()->setClearColour({0.2f, 0.3f, 0.3f, 1.0f});
        Renderer::getAPI()->clear();

        shader->bind();

        vertexArray->bind();
        Renderer::getAPI()->drawIndexed(vertexArray);

        window.update();
    }

    return 0;
}