#pragma once
// Std libs
#include <memory>
#include <vector>
// External libs
#include <spdlog/spdlog.h>

namespace Rum::Core
{
    class Log
    {
    public:
        static void init();

        static std::shared_ptr<spdlog::logger>& getCoreLogger();

        static std::shared_ptr<spdlog::logger>& getClientLogger();

    private:
        static bool isInit;
        static std::shared_ptr<spdlog::logger> mCoreLogger;
        static std::shared_ptr<spdlog::logger> mClientLogger;
    };
} // namespace Rum::Core

//* Global defines for debugging *//
// Engine logging macros
#define RUM_CORE_TRACE(...)    ::Rum::Core::Log::getCoreLogger()->trace(__VA_ARGS__)
#define RUM_CORE_INFO(...)     ::Rum::Core::Log::getCoreLogger()->info(__VA_ARGS__)
#define RUM_CORE_WARN(...)     ::Rum::Core::Log::getCoreLogger()->warn(__VA_ARGS__)
#define RUM_CORE_ERROR(...)    ::Rum::Core::Log::getCoreLogger()->error(__VA_ARGS__)
#define RUM_CORE_CRITICAL(...) ::Rum::Core::Log::getCoreLogger()->critical(__VA_ARGS__)

// Client logging macros
#define RUM_TRACE(...)    ::Rum::Core::Log::getClientLogger()->trace(__VA_ARGS__)
#define RUM_INFO(...)     ::Rum::Core::Log::getClientLogger()->info(__VA_ARGS__)
#define RUM_WARN(...)     ::Rum::Core::Log::getClientLogger()->warn(__VA_ARGS__)
#define RUM_ERROR(...)    ::Rum::Core::Log::getClientLogger()->error(__VA_ARGS__)
#define RUM_CRITICAL(...) ::Rum::Core::Log::getClientLogger()->critical(__VA_ARGS__)