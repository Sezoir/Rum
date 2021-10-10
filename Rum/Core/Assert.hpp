#pragma once
#define RUM_ASSERTS
#ifdef RUM_ASSERTS
#include <string>
#include <Core/Log.hpp>

#if __cplusplus <= 201703L
namespace std
{
    /**
     * Replicates a C++20 feature for C++17.
     * This has been tested on clang-11, GCC 8.10 and VS2019. This may work on earlier versions
     * but has not been tested.
     * For more info look here:
     * https://en.cppreference.com/w/cpp/utility/source_location
     */
    class source_location
    {
    public:
#ifdef __GNUC__
        // GCC doesn't have any kind of implementation for column. So replicate what is shown in
        // <experimental/source_location> always returning 0
        static constexpr source_location current(const char* file = __builtin_FILE(),
                                                 const std::uint_least32_t line = __builtin_LINE(),
                                                 const std::uint_least32_t column = 0,
                                                 const char* function = __builtin_FUNCTION()) noexcept
#else
        static constexpr source_location current(const char* file = __builtin_FILE(),
                                                 const std::uint_least32_t line = __builtin_LINE(),
                                                 const std::uint_least32_t column = __builtin_COLUMN(),
                                                 const char* function = __builtin_FUNCTION()) noexcept
#endif
        {
            return source_location({file, line, column, function});
        }

        [[nodiscard]] constexpr const char* file_name() const noexcept
        {
            return mFile;
        }
        [[nodiscard]] constexpr std::uint_least32_t line() const noexcept
        {
            return mLine;
        }
        [[nodiscard]] constexpr std::uint_least32_t column() const noexcept
        {
            return mColumn;
        }
        [[nodiscard]] constexpr const char* function_name() const noexcept
        {
            return mFunction;
        }

    private:
        constexpr source_location(const char* file, const std::uint_least32_t line, const std::uint_least32_t column,
                                  const char* function)
            : mFile(file)
            , mLine(line)
            , mColumn(column)
            , mFunction(function)
        {
        }

        const char* mFile;
        const uint_least32_t mLine;
        const uint_least32_t mColumn;
        const char* mFunction;
    };
} // namespace std
#else
#include <source_location>
#endif

inline void RUM_CORE_ASSERT(bool check, std::string message = "",
                            const std::source_location location = std::source_location::current())
{
    if(check)
        RUM_CORE_ERROR("{}({}:{}) '{}': Failed assertion with message: {}", location.file_name(), location.line(),
                       location.column(), location.function_name(), message);
}

inline void RUM_ASSERT(bool check, std::string message = "",
                       const std::source_location location = std::source_location::current())
{
    if(check)
        RUM_ERROR("{}({}:{}) '{}': Failed assertion with message: {}", location.file_name(), location.line(),
                  location.column(), location.function_name(), message);
}
#else
#define RUM_CORE_ASSERT(...)
#define RUM_ASSERT(...)
#endif