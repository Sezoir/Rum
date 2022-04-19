cmake_minimum_required(VERSION 3.15)

if (WIN32)
    set(RUM_PLATFORM_TARGET "Windows")
    set(RUM_DEPENDENCY_EXTENSION "lib")
elseif (UNIX)
    set(RUM_PLATFORM_TARGET "UNIX")
    set(RUM_DEPENDENCY_EXTENSION "a")
endif ()
