#include <catch.hpp>
#include <Core/Application.hpp>

TEST_CASE("Testing window", "[WindowPlatform][Window]")
{
    SECTION("Window creation")
    {
        Rum::Core::Application app;
        app.run();
    }
}