#include <catch.hpp>
#include <Core/Log.hpp>
#include <Core/Assert.hpp>

//@TODO: Add a way to check if the log created from assert is valid

TEST_CASE("Test RUM_CORE_ASSERT assert", "[Assert][Core]")
{
    SECTION("Testing no message valid assert")
    {
        RUM_CORE_ASSERT(true);
    }

    SECTION("Testing no message not-valid assert")
    {
        RUM_CORE_ASSERT(false);
    }

    SECTION("Testing message valid assert")
    {
        RUM_CORE_ASSERT(true, "message");
    }

    SECTION("Testing message not-valid assert")
    {
        RUM_CORE_ASSERT(false, "message");
    }
}

TEST_CASE("Test RUM_ASSERT assert", "[Assert][Core]")
{
    SECTION("Testing no message valid assert")
    {
        RUM_ASSERT(true);
    }

    SECTION("Testing no message not-valid assert")
    {
        RUM_ASSERT(false);
    }

    SECTION("Testing message valid assert")
    {
        RUM_ASSERT(true, "message");
    }

    SECTION("Testing message not-valid assert")
    {
        RUM_ASSERT(false, "message");
    }
}