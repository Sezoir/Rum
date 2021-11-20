#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

#include <Rum.hpp>

int main(int argc, char* argv[])
{
    // Initialise logger
    Rum::Core::Log::init();

    // Run the tests
    int result = Catch::Session().run(argc, argv);

    return result;
}