#include <catch.hpp>
#include <Rum.hpp>

struct Position
{
    int x;
    int y;
    int z;

    bool operator==(const Position& rhs) const
    {
        return (x == rhs.x) && (y == rhs.y) && (z == rhs.z);
    }
};

TEST_CASE("Testing Entity creation", "[Scene]")
{
    using namespace Rum::Scene;
    Scene scene;

    SECTION("Testing entity creation")
    {
        Entity& entity = scene.createEntity();
    }

    SECTION("Testing entity creation with component")
    {
        Entity& entity = scene.createEntity();
        entity.addComponent<Position>(1, 2, 3);
        REQUIRE(entity.getComponent<Position>() == Position{1, 2, 3});
    }
}