#include <catch.hpp>
#include <Core/Application.hpp>

TEST_CASE("Testing window", "[Window]")
{
    SECTION("Window creation")
    {
        Engine::Core::Application app;
        app.run();
    }
}