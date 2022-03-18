// Project files
#include "Window.hpp"
#include "Log.hpp"
// Include correct platform window
#ifdef RUM_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.hpp"
#endif

namespace Rum::Core
{
    std::unique_ptr<Window> Window::create(const WindowConfig& windowConfig)
    {
#ifdef RUM_PLATFORM_WINDOWS
        /********************************************************************
         * Windows
         ********************************************************************/

        return std::make_unique<Platform::WindowsWindow>(windowConfig);

#else
        /********************************************************************
         * Unsupported platform
         ********************************************************************/
        assert(false && "Target platform is not supported!");
#endif
    }

} // namespace Rum::Core
