#include <Rum.hpp>
#include <Renderer/FreeRoamCamera.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <Renderer/UniformBuffer.hpp>

int main()
{
    using namespace Rum::Core;
    using namespace Rum::Renderer;

    Application app;

    float vertices[] = {
        // positions        // texture coords
        0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // top right
        0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f,  0.0f, 0.0f, 1.0f  // top left
    };
    uint32_t indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    auto vertexArray = VertexArray::create();
    vertexArray->bind();

    auto vertexBuffer = VertexBuffer::create(vertices, sizeof(vertices), BufferMemoryType::STATIC_DRAW);
    ElementLayout layout = {{ShaderDataType::Float3, "position"}, {ShaderDataType::Float2, "texture"}};
    vertexBuffer->setLayout(layout);
    vertexBuffer->bind();

    auto indicesBuffer =
        IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t), BufferMemoryType::STATIC_DRAW);
    indicesBuffer->bind();

    vertexArray->addVertexObject(vertexBuffer);
    vertexArray->setIndexBuffer(std::move(indicesBuffer));
    vertexArray->unbind();

    auto texture = Rum::Renderer::Texture2D::create("texture.jpg");
    auto shader = Shader::create("triangle", "shader.vert", "shader.frag");
    shader->compile();
    shader->bind();
    shader->setTexture("texture1", texture);
    shader->unbind();

    Rum::Renderer::FreeRoamCamera camera(50, 0.1, 1000, 0, 0, -3.0f, 0, 90, 0);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    auto projection = glm::perspective(glm::radians(45.0f), (float) 800 / (float) 600, 0.1f, 100.0f);

    auto& window = app.getWindow();
    while(window.isOpen())
    {
        window.pollInput();

        Renderer::getAPI()->setClearColour({0.2f, 0.3f, 0.3f, 1.0f});
        Renderer::getAPI()->clear();

        camera.update(0s);

        shader->bind();
        shader->setMat4("model", model);
        shader->setMat4("projection", camera.getProjection());
        shader->setMat4("view", camera.getView());
        vertexArray->bind();
        Renderer::getAPI()->drawIndexed(vertexArray);

        window.update();
    }

    return 0;
}