#include <Rum.hpp>
#include <Renderer/FreeRoamCamera.hpp>
#include <Scene/SceneManager.hpp>

int main()
{
    using namespace Rum::Core;
    using namespace Rum::Renderer;

    Application app;

    auto& scene = app.getSceneManager().makeScene("main");
    app.getSceneManager().setMainScene("main");
    auto camera = std::make_shared<FreeRoamCamera>(50, 0.1, 1000, 0, 0, -3.0f, 0, 90, 0);
    scene.registerCamera(camera);
    auto cube = Renderer::r3D()->createCube(scene, {0, 0, 0}, {1, 1, 1}, {0, 0, 0}, {0, 255, 0, 0});

    return app.run();
}