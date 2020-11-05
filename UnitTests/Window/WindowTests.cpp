#include <catch.hpp>
#include <Core/Application.hpp>

TEST_CASE("Testing window", "[Window]")
{
    SECTION("Window creation")
    {
        Rum::Core::Application app;
        app.run();
    }
}