#include <catch.hpp>
#include <Rum.hpp>
#include <Renderer/Buffers.hpp>

using namespace Rum::Renderer;

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
        REQUIRE(layout.getSize() == 9);
        // Check offset are correctly set
        REQUIRE(layout.getElements()[1].mOffset == 3);
    }
}