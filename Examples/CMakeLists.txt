## Set minimum cmake
cmake_minimum_required(VERSION 3.15)

#########################################################
# Options
#########################################################

option(ENABLE_EXAMPLES "Enables all examples." OFF)


#########################################################
# Examples
#########################################################

if (ENABLE_EXAMPLES)
    add_subdirectory(BasicRectangle)
endif (ENABLE_EXAMPLES)