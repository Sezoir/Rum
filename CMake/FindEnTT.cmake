cmake_minimum_required(VERSION 3.15)

set(DEP_ENTT_VERSION "3.9.0")
set(DEP_ENTT_BUILD_DIR "${PROJECT_SOURCE_DIR}/entt/build/${CMAKE_BUILD_TYPE}---${CMAKE_CXX_COMPILER_ID}")
set(DEP_ENTT_SOURCE_DIR "${PROJECT_SOURCE_DIR}/entt/entt-${DEP_ENTT_VERSION}")
set(DEP_ENTT_INSTALL_DIR "")

if (RUM_BUILD_LIBS_METHOD STREQUAL PREBUILD)
    execute_process(COMMAND cmake -DCMAKE_MAKE_PROGRAM=${CMAKE_MAKE_PROGRAM} -G ${CMAKE_GENERATOR} -B ${DEP_ENTT_BUILD_DIR} -S ${DEP_ENTT_SOURCE_DIR})

    add_custom_target(enttBuild COMMAND cmake --build ${DEP_ENTT_BUILD_DIR} BYPRODUCTS ${DEP_ENTT_BUILD_DIR}/src/EnTTConfig.cmake)

    list(APPEND CMAKE_PREFIX_PATH ${DEP_ENTT_BUILD_DIR})

    # Get packages
    find_package(EnTT CONFIG REQUIRED)

elseif (RUM_BUILD_LIBS_METHOD STREQUAL STATIC)
    add_subdirectory(${DEP_ENTT_SOURCE_DIR})
endif ()
