#include "Log.hpp"

// External libs
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Rum::Core
{
    bool Log::isInit = false;
    std::shared_ptr<spdlog::logger> Log::mCoreLogger;
    std::shared_ptr<spdlog::logger> Log::mClientLogger;

    void Log::init()
    {
        // Create 2 sinks: console sink and a file sink
        std::vector<spdlog::sink_ptr> sinks;
        sinks.push_back(std::make_shared<spdlog::sinks::stderr_color_sink_st>());
        sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_st>("Rum.log", true));

        // Set the pattern
        sinks[0]->set_pattern("%^ [%T] [%l] %n: %v %$");
        sinks[1]->set_pattern("%^ [%T] [%l] %n: %v %$");

        // Set the console sink to only show log levels that are warnings or higher
        sinks[0]->set_level(spdlog::level::info);
        sinks[1]->set_level(spdlog::level::trace);

        // Create a logger for the engine
        mCoreLogger = std::make_shared<spdlog::logger>("Rum", begin(sinks), end(sinks));
        spdlog::register_logger(mCoreLogger);
        mCoreLogger->set_level(spdlog::level::trace);
        mCoreLogger->flush_on(spdlog::level::trace);

        // Create a logger for the application
        mClientLogger = std::make_shared<spdlog::logger>("Application", begin(sinks), end(sinks));
        spdlog::register_logger(mClientLogger);
        mClientLogger->set_level(spdlog::level::trace);
        mClientLogger->flush_on(spdlog::level::trace);

        isInit = true;
    }

    std::shared_ptr<spdlog::logger>& Log::getCoreLogger()
    {
        // @todo: Change from assert
        assert(isInit);
        return mCoreLogger;
    }

    std::shared_ptr<spdlog::logger>& Log::getClientLogger()
    {
        // @todo: Change from assert
        assert(isInit);
        return mClientLogger;
    }
} // namespace Rum::Core