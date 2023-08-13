cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_STANDARD 17)
project(mather)

option(MATHER_BUILD_DEMO "Build the demo" ON)

add_subdirectory(lib)
include_directories(include/)

if (APPLE)
    list(APPEND OS_DEPENDANT "-framework OpenGL")
elseif (WIN32)
    list(APPEND OS_DEPENDANT "-lglu32 -lopengl32")
    set(CMAKE_EXE_LINKER_FLAGS "-std=gnu99 -static -static-libgcc -static-libstdc++ -mwindows")
else ()
    list(APPEND OS_DEPENDANT "-lGL -lGLU -lX11")
endif ()

add_library(mather include/mather.hpp include/path.hpp src/mather.cpp include/drawers.hpp src/drawers.cpp)
target_link_libraries(mather glfw agg ${OS_DEPENDANT})

if (MATHER_BUILD_DEMO)
    add_executable(mather-demo demo/main.cpp)
    target_link_libraries(mather-demo mather)
endif ()


