cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_STANDARD 17)
project(mather)

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

add_library(mather include/mather.hpp src/mather.cpp)
target_link_libraries(mather glfw agg ${OS_DEPENDANT})

add_executable(mather-example src/main.cpp)
target_link_libraries(mather-example mather)
