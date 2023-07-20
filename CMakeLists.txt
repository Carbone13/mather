cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_STANDARD 17)
project(mather)

option(MATHER_BUILD_DEMO "Build the demo" ON)

add_subdirectory(lib)
include_directories(include/)

add_library(mather include/mather.hpp include/path.hpp src/mather.cpp include/drawers.hpp src/drawers.cpp)
target_link_libraries(mather agg ${OS_DEPENDANT})

if (MATHER_BUILD_DEMO)
    add_subdirectory(demo)
endif ()


